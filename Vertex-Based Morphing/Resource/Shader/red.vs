#version 450

layout (location = 0) in vec3 Position;

uniform mat4 view;

void main()
{
    gl_Position = view * vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0);
}