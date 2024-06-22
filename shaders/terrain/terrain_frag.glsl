#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;

void main() {
    vec3 color = vec3(1.0, 1.0, 1.0);

    vec3 diffuseTexture = texture(texture1, TexCoord).rgb;
    vec3 lightDir = normalize(vec3(-4.0, 14.0, 12.0) - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = vec3(1.0, 1.0, 1.0) * diff;

    FragColor = texture(texture1, TexCoord);
}