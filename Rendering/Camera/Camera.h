#pragma once

#include <Utilities\Container\Matrix4.h>
#include <Utilities\Container\Vector3.h>

class Camera final {
public:
	const Matrix4 ViewMatrix() const;
private:
	Camera() = delete;
	~Camera() = delete;

	static Vector3 m_position{ 0.0f,0.0f,0.0f };
	static Vector3 m_direction{ 0.0f,0.0f,1.0f };
};