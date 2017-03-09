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
	float morph;
};

layout(std140) uniform Block_Perspective {
	mat4 projection;
	mat4 view;
};

layout(std140) uniform Block_Material {
	Material material[2];
};

layout(location = 0) in Vertex vertex[2];
layout(location = 6) in Instance instance;

out vec3 o_normal;

void main()
{
	Material mat = material[instance.material];

	mat4 MVP = projection * view * instance.transform;
	gl_Position = MVP * vec4(mix(vertex[0].position, vertex[1].position, mat.morph), 1.0);
	o_normal = mix(vertex[0].normal, vertex[1].normal, mat.morph) * mat.colour;
}