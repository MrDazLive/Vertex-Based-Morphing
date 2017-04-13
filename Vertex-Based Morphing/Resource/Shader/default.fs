#version 450

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 uv;
};

uniform sampler2D textures[4];

in Vertex o_vertex;
flat in int o_diffuse;

out vec4 colour;

void main()
{
    colour = texture(textures[o_diffuse], o_vertex.uv);
}