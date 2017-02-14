#version 450

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 o_normal;

void main()
{
	mat4 MVP = projection * view * model;
    gl_Position = MVP * vec4(position, 1.0);
	o_normal = normal;
}