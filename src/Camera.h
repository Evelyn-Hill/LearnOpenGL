#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "VectorMacros.h"

class Camera {
public:
	Camera(vec3 startingPosition, int screenWidth, int screenHeight, float lookSens, float moveSpeed);
	~Camera();
	
	mat4 lookingAt;
	mat4 projection;

	vec3 position;

	vec3 front;
	vec3 up;
	
	float pitch;
	float yaw;

	float lookSensitivity;
	float moveSpeed;
	
	void UpdateLookingAt();

private:
	int screenWidth;
	int screenHeight;
};

