#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;      // Fragment position in world coordinates
out vec3 Normal;       // Normal direction in world coordinates
out vec2 TexCoords;    // Texture coordinates to fragment shader

uniform mat4 model;    // Model matrix
uniform mat4 view;     // View matrix
uniform mat4 projection; // Projection matrix

void main() {
    // Transform vertex position and normal to world coordinates
    vec4 worldPos = model * vec4(aPos, 1.0);
    FragPos = vec3(worldPos);
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Pass texture coordinates
    TexCoords = aTexCoords;

    // Output position in clip coordinates
    gl_Position = projection * view * worldPos;
}