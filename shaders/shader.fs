#version 330 core

in vec3 vertexColor;

out vec4 FragColor;

uniform vec3 fragColor;

void main() {
    FragColor = vec4(fragColor, 1.0);

    //first
    //FragColor = vec4(mix(fragColor1, fragColor2, fragValue), 1.0);

    //secound
    //vec3 color = mix(fragColor1, fragColor2, fragValue);
    //FragColor = vec4(step(0.5, color.r), step(0.5, color.g), 0.0, 1.0);

    //third
    //vec3 color = mix(fragColor1, fragColor2, fragValue);
    //FragColor = vec4(smoothstep(0.4, 0.6, color.r), smoothstep(0.4, 0.6, color.g), 0.0, 1.0);

    //fourth
    //vec3 color = sin(4 * mix(fragColor1, fragColor2, fragValue) * 3.14);
    //FragColor = vec4(color, 1.0);

    //fifth
    //vec3 color = sin(4 * mix(fragColor1, fragColor2, fragValue) * 3.14);
    //FragColor = vec4(step(0, color.r), step(0, color.g), 0.0, 1.0);
}