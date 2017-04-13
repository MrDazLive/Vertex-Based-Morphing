#version 400
#define PI 3.1415926535897932384626433832795

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 uv;
};

struct Instance {
	mat4 transform;
	uint material[2];
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

layout(location = 0) in Vertex vertex[2];
layout(location = 6) in float morphWeight;
layout(location = 7) in Instance instance;

out vec3 o_normal;

subroutine vec3 Interpolate(vec3, vec3, float);
subroutine uniform Interpolate interpolate;

subroutine(Interpolate) vec3 linear(vec3 min, vec3 max, float morph) {
	float weight = morph;
	return mix(min, max, weight);
}

subroutine(Interpolate) vec3 cosine(vec3 min, vec3 max, float morph) {
	float weight = sin(morph * PI / 2);
	return mix(min, max, weight);
}

subroutine(Interpolate) vec3 quadratic(vec3 min, vec3 max, float morph) {
	float weightA = morph;
	float weightB = 1 - weightA;

	float a = 0.0f;
	float b = 0.5f;
	float c = 1.0f;

	float weight = a * weightB * weightB
					+ b * weightA * weightB
					+ c * weightA * weightA;

	return mix(min, max, weight);
}

subroutine(Interpolate) vec3 cubic(vec3 min, vec3 max, float morph) {
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
	
	return mix(min, max, weight);
}

void main()
{
	mat4 MVP = projection * view * instance.transform;
	gl_Position = MVP * vec4(interpolate(vertex[0].position, vertex[1].position, material[instance.material[0]].morph), 1.0);
	o_normal = interpolate(vertex[0].normal, vertex[1].normal, material[instance.material[0]].morph) * material[instance.material[0]].colour;
}