#version 330 core

struct Material {
    vec3 ambient;       // Ambient reflectivity of the material
    vec3 diffuse;       // Diffuse reflectivity of the material
    vec3 specular;      // Specular reflectivity of the material
    float shininess;    // Shininess coefficient for specular highlights
};

out vec4 FragColor;

in vec3 FragPos;    // Position of the fragment in world space
in vec3 Normal;     // Normal vector at the fragment in world space
in vec2 TexCoord;

uniform Material material;      // Material properties
uniform vec3 objColor;          // Base color of the object
uniform vec3 lightColor;        // Color of the light
uniform vec3 lightPos;          // Position of the light
uniform vec3 viewPos;           // Position of the camera

uniform sampler2D texture1;

void main() {
    // Calculate ambient light
    // Ambient light is a constant light that affects all surfaces equally, simulating indirect lighting.
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * (lightColor * material.ambient);

    // Calculate diffuse light
    // Diffuse light simulates the directional light hitting the surface and scattering in all directions.
    // It depends on the angle between the light direction and the surface normal.
    vec3 lightDirection = normalize(lightPos - FragPos);                                        // Direction from the fragment to the camera
    vec3 diffuse = max(dot(Normal, lightDirection), 0.0) * (lightColor * material.diffuse);     // Halfway vector between light direction and view direction

    // Calculate specular light
    // Specular light simulates the bright spot of light that appears on shiny objects.
    // It depends on the view direction, light direction, and the shininess of the material.
    vec3 viewDirection = normalize(viewPos - FragPos); //a
    vec3 halfWayDirection = normalize(lightDirection + viewDirection); //h
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
    vec3 specular = pow(max(dot(Normal, halfWayDirection), 0.0), material.shininess) * (lightColor * material.specular);

    // Combine all lighting components
    // The final color is a combination of ambient, diffuse, and specular lighting, all scaled by the object's base color.
    vec3 lightingResult = (ambient + diffuse + specular) * objColor;

    // Set the fragment color
    // Output the final color of the fragment with full opacity.
    //FragColor = vec4(lightingResult, 1.0);
    // Output the final color of the fragment with full opacity and Texture.
    FragColor = texture(texture1, TexCoord) * vec4(lightingResult, 1.0);
}