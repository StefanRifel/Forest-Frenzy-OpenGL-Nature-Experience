#version 330 core

struct Material {
    vec3 emissive;
    vec3 ambient;       // Ambient reflectivity of the material
    vec3 diffuse;       // Diffuse reflectivity of the material
    vec3 specular;      // Specular reflectivity of the material
    float shininess;    // Shininess coefficient for specular highlights
    float density;
    float dissolve;
    float illumination;
};

in vec3 FragPos;    // Position of the fragment in world space
in vec3 Normal;     // Normal vector at the fragment in world space
in vec2 TexCoord;

out vec4 FragColor;

uniform Material material;      // Material properties
uniform vec3 lightColor;        // Color of the light
uniform vec3 lightPos;          // Position of the light
uniform vec3 viewPos;           // Position of the camera

uniform sampler2D texture1;

void main() {
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * (lightColor * material.ambient);

    vec3 lightDirection = normalize(lightPos - FragPos);
    vec3 diffuse = max(dot(Normal, lightDirection), 0.0) * (lightColor * material.diffuse);

    vec3 viewDirection = normalize(viewPos - FragPos); //a
    vec3 halfWayDirection = normalize(lightDirection + viewDirection); //h

    vec3 specular = pow(max(dot(Normal, halfWayDirection), 0.0), material.shininess) * (lightColor * material.specular);

    vec3 lightingResult = (material.emissive + ambient + diffuse + specular);

    FragColor = texture(texture1, TexCoord) * vec4(lightingResult, 1.0);
}