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
	vec3 dir = normalize(vec3(-1, -1, -1));
	vec3 norm = o_vertex.normal;

	float offset = dot(-dir, norm) / 2 + 0.5f;

    colour = offset * texture(textures[o_diffuse], o_vertex.uv);
}