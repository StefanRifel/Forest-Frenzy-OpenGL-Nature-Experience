#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D moonTexture;
uniform vec3 lightColor;

void main() {
    vec4 texColor = texture(moonTexture, TexCoords);

    FragColor = vec4(texColor.rgb * lightColor, texColor.a);
}