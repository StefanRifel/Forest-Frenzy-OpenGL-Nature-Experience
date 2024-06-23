#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform vec2 resolution; // Screen resolution

void main()
{
    // Sample the screen texture
    vec4 texColor = texture(screenTexture, TexCoords);

    // Calculate vignette effect for top and bottom edges
    float topVignette = smoothstep(0.0, 0.4, TexCoords.y);
    float bottomVignette = smoothstep(1.0, 0.6, TexCoords.y);

    // Combine top and bottom vignette effects
    float vignette = topVignette * bottomVignette;

    // Darken the edges with vignette effect
    vec3 darkenedColor = texColor.rgb * vignette;

    // Add subtle ambient light
    vec3 ambientColor = vec3(0.02); // Adjust ambient light intensity
    vec3 finalColor = darkenedColor + ambientColor;

    // Output final color
    FragColor = vec4(finalColor, texColor.a);
}
