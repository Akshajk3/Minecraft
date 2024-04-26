#version 330 core

out vec4 FragColor;

in float shading;
in vec2 texCoord;
in float FogFactor;

uniform sampler2D tex0;
uniform vec3 fogColor;

void main()
{
    vec4 texColor = texture(tex0, texCoord) * shading;
    
    // Increase the fog color intensity
    vec3 intensifiedFogColor = fogColor; // Adjust this multiplier as needed

    vec4 finalColor = vec4(texColor.rgb, texColor.a * 0.5);
    
    FragColor = finalColor;
}