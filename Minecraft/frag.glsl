#version 330 core

out vec4 FragColor;

in float shading;
in vec2 texCoord;
in float FogFactor;

uniform sampler2D tex0;
uniform vec3 fogColor;

void main()
{
    // Sample the texture color
    vec4 texColor = texture(tex0, texCoord) * shading;

    // If the alpha value is less than a certain threshold, discard the fragment
    if (texColor.a < 0.1) { // Adjust the threshold as needed
        //discard;
    }

    // Blend texture color with fog color based on fog factor
    vec3 blendedColor = mix(texColor.rgb, fogColor, FogFactor);

    // Final color with full alpha (1.0)
    vec4 finalColor = vec4(blendedColor, 1.0);

    FragColor = finalColor;
}
