#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform vec3 lightPos; // Position of the light source in world space
uniform vec3 viewPos;  // Position of the camera (or viewer) in world space

void main() {
    vec3 ambientColor = vec3(0.1f, 0.1f, 0.15f); // Ambient light color
    vec3 diffuseColor = vec3(0.8f, 0.6f, 0.5f); // Diffuse light color
    vec3 specularColor = vec3(0.9f, 0.8f, 0.7f); // Specular light color

    // Material properties (you might want to set these via uniforms)
    vec3 materialAmbient = vec3(1.0, 1.0, 1.0);
    vec3 materialDiffuse = texture(texture1, TexCoord).rgb;
    vec3 materialSpecular = vec3(0.5, 0.5, 0.5);
    float shininess = 32.0;

    // Calculate lighting
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // Ambient component
    vec3 ambient = ambientColor * materialAmbient;

    // Diffuse component
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diffuseColor * (materialDiffuse * diff);

    // Specular component (using Blinn-Phong)
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), shininess);
    vec3 specular = specularColor * (materialSpecular * spec);

    // Combine all components
    vec3 result = ambient + diffuse + specular;

    // Output final color
    FragColor = vec4(result, 1.0) * texture(texture1, TexCoord);
}