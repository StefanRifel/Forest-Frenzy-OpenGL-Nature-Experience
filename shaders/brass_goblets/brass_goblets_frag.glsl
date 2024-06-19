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

// Constants
const float PI = 3.14159265359;

// Cook-Torrance BRDF
vec3 CookTorranceBRDF(vec3 viewDir, vec3 lightDir, vec3 normal, float roughness, vec3 F0) {
    // Fresnel-Schlick approximation
    float NdotL = max(dot(normal, lightDir), 0.0);
    float NdotV = max(dot(normal, viewDir), 0.0);
    vec3 H = normalize(viewDir + lightDir);
    float NdotH = max(dot(normal, H), 0.0);
    float LdotH = max(dot(lightDir, H), 0.0);

    // Geometric attenuation (Smith's method)
    float alpha = roughness * roughness;
    float alpha2 = alpha * alpha;
    float G = min(1.0, min(2.0 * NdotH * NdotV / LdotH, 2.0 * NdotH * NdotL / LdotH));

    // Microfacet distribution (GGX)
    float D = alpha2 / (PI * pow(NdotH * NdotH * (alpha2 - 1.0) + 1.0, 2.0));

    // Fresnel term
    vec3 F = F0 + (1.0 - F0) * pow(1.0 - LdotH, 5.0);

    // Specular term
    vec3 numerator = D * G * F;
    float denominator = 4.0 * max(NdotV, 0.001) * max(NdotL, 0.001); // Avoid division by zero
    vec3 specular = numerator / denominator;

    return specular;
}

void main() {
    // Ambient
    vec3 ambient = light.ambient * material.ambient;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseColor = texture(textures.texture_diffuse, TexCoords).rgb;
    vec3 diffuse = light.diffuse * (diff * diffuseColor);

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    // Sample roughness and metalness maps (if available)
    float roughness = texture(textures.texture_roughness, TexCoords).r;
    float metalness = texture(textures.texture_metalness, TexCoords).r;
    vec3 specularColor = mix(vec3(0.04), material.specular, metalness); // Approximate F0

    vec3 specular = CookTorranceBRDF(viewDir, lightDir, norm, roughness, specularColor);

    vec3 result = diffuseColor * (ambient + diffuse + specular + material.emissive);

    FragColor = vec4(result, 1.0);
}
