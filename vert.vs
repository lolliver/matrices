#version 330

layout(location=0) in vec2 position;
layout(location=1) in vec3 color;
layout(location=2) in vec2 texcoords;

out vec3 Color;
out vec2 Texcoords;

void main()
{
    Color = color;
    Texcoords = vec2(texcoords.x, 1.0f - texcoords.y);
    gl_Position = vec4(position,0.0,1.0);
}
