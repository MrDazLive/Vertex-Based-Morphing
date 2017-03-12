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

subroutine vec3 Interpolate(vec3, vec3);
subroutine uniform Interpolate interpolate;

subroutine(Interpolate) vec3 linear(vec3 min, vec3 max) {
	float weight = material[instance.material].morph;
	return mix(min, max, weight);
}

subroutine(Interpolate) vec3 cosine(vec3 min, vec3 max) {
	float weight = sin(material[instance.material].morph * PI / 2);
	return mix(min, max, weight);
}

subroutine(Interpolate) vec3 quadratic(vec3 min, vec3 max) {
	float weightA = material[instance.material].morph;
	float weightB = 1 - weightA;

	float a = 0.0f;
	float b = 0.5f;
	float c = 1.0f;

	float weight = a * weightB * weightB
					+ b * weightA * weightB
					+ c * weightA * weightA;

	return mix(min, max, weight);
}

subroutine(Interpolate) vec3 cubic(vec3 min, vec3 max) {
	float weightA = material[instance.material].morph;
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
	gl_Position = MVP * vec4(interpolate(vertex[0].position, vertex[1].position), 1.0);
	o_normal = interpolate(vertex[0].normal, vertex[1].normal) * material[instance.material].colour;
}