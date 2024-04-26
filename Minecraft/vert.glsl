#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in float aShading;

out float shading;
out vec2 texCoord;
out float FogFactor;

uniform mat4 view;        // Updated uniform name
uniform mat4 projection;  // Updated uniform name
uniform vec3 cameraPos;

void main()
{
    gl_Position = projection * view * vec4(aPos, 1.0);
    shading = aShading;
    texCoord = aTex;

    // Calculate the distance of the fragment from the camera
    float distance = length(cameraPos - aPos);

    const float fogStart = 10.0;
    const float fogEnd = 50.0;
    float fogDensity = 0.2;
    FogFactor = clamp((fogEnd - distance) / (fogEnd - fogStart), 0.0, 1.0);
    FogFactor = 1.0 - exp(-FogFactor * fogDensity);
}
