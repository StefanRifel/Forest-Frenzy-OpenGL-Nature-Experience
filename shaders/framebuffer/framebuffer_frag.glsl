#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 col = texture(screenTexture, TexCoords).rgb * vec3(0.6, 0.6, 0.6);
    FragColor = vec4(col, 1.0);
}