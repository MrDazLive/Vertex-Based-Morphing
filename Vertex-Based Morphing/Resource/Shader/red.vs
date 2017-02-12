#version 450

layout (location = 0) in vec3 Position;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(0.5 * Position.x, 0.5 * Position.y, Position.z, 1.0);
}