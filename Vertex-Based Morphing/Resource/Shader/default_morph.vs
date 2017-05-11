#version 400
#define PI 3.1415926535897932384626433832795

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
	float morphDiffuse;

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

layout(location = 0) in Vertex vertex[2];
layout(location = 6) in float morphWeight;
layout(location = 7) in Instance instance;

out float o_morph;
out Vertex o_vertex[2];
flat out Material o_material;

subroutine float ConvertWeight(float);
subroutine uniform ConvertWeight convertWeight;

subroutine(ConvertWeight) float linear(float morph) {
	float weight = morph;
	return weight;
}

subroutine(ConvertWeight) float cosine(float morph) {
	float weight = sin(morph * PI / 2);
	return weight;
}

subroutine(ConvertWeight) float quadratic(float morph) {
	float weightA = morph;
	float weightB = 1 - weightA;

	float a = 0.0f;
	float b = 0.5f;
	float c = 1.0f;

	float weight = a * weightB * weightB
					+ b * weightA * weightB
					+ c * weightA * weightA;

	return weight;
}

subroutine(ConvertWeight) float cubic(float morph) {
	float weightA = morph;
	float weightB = 1 - weightA;

	float a = 0.0f;
	float b = 0.1f;
	float c = 0.9f;
	float d = 1.0f;

	float weight = a * weightB * weightB * weightB
					+ b * weightA * weightB * weightB
					+ c * weightA * weightA * weightB
					+ d * weightA * weightA * weightA;
	
	return weight;
}

void main()
{
	mat4 MVP = projection * view * instance.transform;
	float weight = convertWeight(material[instance.material].morph);

	o_morph = weight;
	o_vertex = vertex;
	o_material = material[instance.material];

	gl_Position = MVP * vec4(mix(vertex[0].position, vertex[1].position, weight), 1.0);
}