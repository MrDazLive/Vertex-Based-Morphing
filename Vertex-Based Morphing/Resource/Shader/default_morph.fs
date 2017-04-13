#version 450

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 uv;
};

struct Material {
	vec3 colour;
	float diffuse;
	float morph;
	float morphDiffuse;

	float pad2;
	float pad3;
};

uniform sampler2D textures[4];

in float o_morph;
in Vertex[2] o_vertex;
flat in Material o_material;

out vec4 colour;

void main()
{
    colour = mix(
		texture(textures[int(o_material.diffuse)], o_vertex[0].uv),
		texture(textures[int(o_material.morphDiffuse)], o_vertex[1].uv),
		o_morph);
}
