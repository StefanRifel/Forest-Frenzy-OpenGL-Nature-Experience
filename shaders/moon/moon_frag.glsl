#version 330 core
out vec4 FragColor;

struct Texture {
    sampler2D moon;
};

struct Light {
    vec3 color;
};

in vec2 TexCoords;

uniform Texture textures;
uniform Light light;

void main() {
    vec4 texColor = texture(textures.moon, TexCoords);

    FragColor = vec4(texColor.rgb * light.color, texColor.a);
}