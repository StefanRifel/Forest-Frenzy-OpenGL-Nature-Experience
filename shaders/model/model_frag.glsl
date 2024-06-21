#version 330 core

out vec4 FragColor;   // Fragment shader output color

// Material struct
struct Material {
    vec3 emissive;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

// Texture struct
struct Texture {
    sampler2D texture_diffuse;
    sampler2D texture_normal;
    sampler2D texture_ambient;
    sampler2D texture_metalness;
    sampler2D texture_roughness;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;      // Fragment position in world coordinates
in vec3 Normal;       // Normal direction in world coordinates
in vec2 TexCoords;    // Texture coordinates from vertex shader

uniform Material material;
uniform Texture textures; // Now includes all texture samplers
uniform Light light;

uniform vec3 viewPos; // Camera/viewer position

void main() {
    // Calculate ambient light
    // Ambient light is a constant light that affects all surfaces equally, simulating indirect lighting.
    float ambientStrength = texture(textures.texture_ambient, TexCoords).r;
    vec3 ambient = ambientStrength * (light.ambient *  material.ambient);


    vec3 normal = texture(textures.texture_normal, TexCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);

    // Calculate diffuse light
    // Diffuse light simulates the directional light hitting the surface and scattering in all directions.
    // It depends on the angle between the light direction and the surface normal.
    vec3 diffuseTexture = texture(textures.texture_diffuse, TexCoords).rgb;
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * material.diffuse * diff * diffuseTexture;

    // Calculate specular light
    // Specular light simulates the bright spot of light that appears on shiny objects.
    // It depends on the view direction, light direction, and the shininess of the material.
    float roughtness = texture(textures.texture_roughness, TexCoords).r;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfWayDir = normalize(lightDir + viewDir);
    //     Halfway vector (h) used in Blinn-Phong reflection model
    //         ^
    //        / \
    //       /   \
    //      /     \
    //   v /.......\ l
    //    /         \
    //   /           \
    //  /             \
    // View (v)     Light (l)
    float spec = pow(max(dot(Normal, halfWayDir), 0.0), material.shininess);
    vec3 specular = vec3(0.2) * (roughtness * spec * (light.specular * material.specular));

    // Combine all lighting components
    // The final color is a combination of ambient, diffuse, and specular lighting, all scaled by the object's base color.
    vec3 result = ambient + diffuse + specular + material.emissive;

    FragColor = vec4(diffuseTexture , 1.0);
}
