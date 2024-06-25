#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform vec3 lightPos; // Position of the light source in world space
uniform vec3 viewPos;  // Position of the camera (or viewer) in world space

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

uniform Flashlight flashlight;

uniform bool flashLightOn;

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

    // Combine all components from the main light source
    vec3 result = ambient + diffuse + specular;

    // Calculate flashlight influence
    vec3 norm = normalize(Normal);
    vec3 lightFDir = normalize(flashlight.position - FragPos);
    float theta = dot(lightFDir, normalize(-flashlight.direction));
    float epsilon = (flashlight.cutOff - flashlight.outerCutOff);
    float intensity = smoothstep(flashlight.outerCutOff, flashlight.cutOff, theta);

    if (intensity > 0.0 && flashLightOn) {
        // Flashlight ambient
        vec3 flashlightAmbient = flashlight.ambient * texture(texture1, TexCoord).rgb;

        // Flashlight diffuse
        float flashlightDiff = max(dot(norm, lightFDir), 0.0);
        vec3 flashlightDiffuse = flashlight.diffuse * flashlightDiff * texture(texture1, TexCoord).rgb;

        // Flashlight specular
        float roughness = 0.5; // Roughness could be another uniform or texture value
        vec3 reflectDir = reflect(-lightFDir, norm);
        float flashlightSpec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        vec3 flashlightSpecular = flashlight.specular * (flashlightSpec * roughness);

        // Apply intensity to flashlight components
        flashlightDiffuse *= intensity;
        flashlightSpecular *= intensity;

        // Attenuation for flashlight
        float distance = length(flashlight.position - FragPos);
        float attenuation = 1.0 / (flashlight.constant + flashlight.linear * distance + flashlight.quadratic * (distance * distance));
        flashlightAmbient *= attenuation;
        flashlightDiffuse *= attenuation;
        flashlightSpecular *= attenuation;

        // Combine all components from the flashlight
        vec3 flashlightResult = flashlightAmbient + flashlightDiffuse + flashlightSpecular;

        // Add flashlight result to the main light result
        result += flashlightResult;
    }

    // Output final color
    FragColor = vec4(result, 1.0) * texture(texture1, TexCoord);
}