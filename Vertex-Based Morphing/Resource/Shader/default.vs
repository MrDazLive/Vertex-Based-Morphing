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
	float diffuse;
	float morph;
	
	float pad1;
	float pad2;
	float pad3;
};

layout(std140) uniform Block_Perspective {
	mat4 projection;
	mat4 view;
};

layout(std140) uniform Block_Material {
	Material material[3];
};

layout(location = 0) in Vertex vertex;
layout(location = 3) in Instance instance;

out Vertex o_vertex;
flat out int o_diffuse;

void main()
{
	mat4 MVP = projection * view * instance.transform;
	gl_Position = MVP * vec4(vertex.position, 1.0);
	o_vertex = vertex;
	o_diffuse = int(material[instance.material].diffuse);
	o_vertex.normal = vertex.normal * material[instance.material].colour;
}