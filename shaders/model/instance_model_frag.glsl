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

struct Flashlight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;      // Fragment position in world coordinates
in vec3 Normal;       // Normal direction in world coordinates
in vec2 TexCoords;    // Texture coordinates from vertex shader

uniform Material material;
uniform Texture textures; // Now includes all texture samplers
uniform Light light;
uniform Flashlight flashlight;

uniform vec3 viewPos; // Camera/viewer position

void main() {
    // Calculate flashlight influence
    vec3 norm = normalize(Normal);
    vec3 lightFDir = normalize(flashlight.position - FragPos);
    float theta = dot(lightFDir, normalize(-flashlight.direction));
    float epsilon = (flashlight.cutOff - flashlight.outerCutOff);
    float intensity = smoothstep(flashlight.outerCutOff, flashlight.cutOff, theta);

    if(intensity > 0.0) {
        // Ambient
        vec3 ambient = flashlight.ambient * texture(textures.texture_diffuse, TexCoords).rgb;

        // Diffuse
        float diff = max(dot(norm, lightFDir), 0.0);
        vec3 diffuse = flashlight.diffuse * diff * texture(textures.texture_diffuse, TexCoords).rgb;

        // Specular
        float roughness = texture(textures.texture_roughness, TexCoords).r;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightFDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = flashlight.specular * (spec * roughness);

        // Apply intensity
        diffuse *= intensity;
        specular *= intensity;

        // Attenuation
        float distance = length(flashlight.position - FragPos);
        float attenuation = 1.0 / (flashlight.constant + flashlight.linear * distance + flashlight.quadratic * (distance * distance));
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        vec3 result = ambient + diffuse + specular;
        FragColor = vec4(result, 1.0);
    } else {
        // Calculate ambient light
        float ambientStrength = texture(textures.texture_ambient, TexCoords).r;
        vec3 ambient = ambientStrength * (light.ambient *  material.ambient);

        vec3 normal = texture(textures.texture_normal, TexCoords).rgb;
        normal = normalize(normal * 2.0 - 1.0);

        // Calculate diffuse light
        vec3 diffuseTexture = texture(textures.texture_diffuse, TexCoords).rgb;
        vec3 lightDir = normalize(light.position - FragPos);
        float diff = max(dot(Normal, lightDir), 0.0);
        vec3 diffuse = light.diffuse * material.diffuse * diff * diffuseTexture;

        // Calculate specular light
        float roughness = texture(textures.texture_roughness, TexCoords).r;
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 halfWayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(Normal, halfWayDir), 0.0), material.shininess);
        vec3 specular = vec3(0.2) * (roughness * spec * (light.specular * material.specular));

        // Combine all lighting components
        vec3 result = ambient + diffuse + specular + material.emissive;

        FragColor = vec4(result, 1.0);
    }
}