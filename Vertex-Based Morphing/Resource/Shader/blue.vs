#version 400

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 uv;
};

struct Instance {
	mat4 transform;
	uint material;
};

struct Material {
	vec3 colour;
	float pad;
};

layout(std140) uniform Block_Perspective {
	mat4 projection;
	mat4 view;
};

layout(std140) uniform Block_Material {
	Material material[2];
};

layout(location = 0) in Vertex vertex;
layout(location = 3) in Instance instance;

out vec2 o_uv;

void main()
{
	mat4 MVP = projection * view * instance.transform;
	gl_Position = MVP * vec4(vertex.position, 1.0);
	o_uv = vertex.uv;
}