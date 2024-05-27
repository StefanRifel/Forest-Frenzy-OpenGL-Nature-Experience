#version 330 core

in vec3 vertexColor;
in vec3 normal;

out vec4 FragColor;

uniform vec3 fragColor;

void main() {
    FragColor = vec4(fragColor, 1.0);
}