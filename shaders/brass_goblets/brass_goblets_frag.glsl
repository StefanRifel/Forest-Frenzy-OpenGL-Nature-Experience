#version 330 core

out vec4 FragColor;   // Fragment shader output color

// Material struct
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Texture struct
struct Texture {
    sampler2D texture_diffuse; //diff
    sampler2D texture_specular;
    sampler2D texture_reflect; //spec
    sampler2D texture_normal;
};

in vec3 FragPos;      // Fragment position in world coordinates
in vec3 Normal;       // Normal direction in world coordinates
in vec2 TexCoords;    // Texture coordinates from vertex shader

uniform Material material;
uniform Texture textures;
uniform Light light;

uniform vec3 viewPos; // Camera/viewer position

void main() {
    // ambient
    vec3 ambient = light.ambient * texture(textures.texture_diffuse, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(textures.texture_diffuse, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(textures.texture_reflect, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
