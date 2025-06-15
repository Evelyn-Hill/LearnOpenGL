#include "Camera.h"

Camera::Camera(vec3 startingPosition, int screenWidth, int screenHeight, float lookSens, float moveSpeed)
{
	// Setup camera data.
	position = startingPosition;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	lookSensitivity = lookSens;
	this->moveSpeed = moveSpeed;
	front = vec3(0.0f, 0.0f, -1.0f);
	up = vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.0f;
	pitch = 0.0f;
	

	lookingAt  = mat4(1);
	// setup look at.
	lookingAt = glm::lookAt(position, position + front, up);

	projection  = mat4(1);
	projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f); 
}

void Camera::UpdateLookingAt()
{
	lookingAt = glm::lookAt(position, position + front, up);
}

