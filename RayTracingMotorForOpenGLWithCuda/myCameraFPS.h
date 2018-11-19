#pragma once
#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

enum Camera_Movement {
	C_FORWARD = 0,
	C_BACKWARD,
	C_LEFT,
	C_RIGHT
};

// Default camera values
constexpr auto YAW = -90.0f;
constexpr auto PITCH = 0.0f;
constexpr auto SPEED = 3.0f;
constexpr auto SENSITIVTY = 0.25f;
constexpr auto ZOOM = 45.0f;

class myCameraFPS
{
public:
	myCameraFPS(
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
		float yaw = YAW, float pitch = PITCH);

	~myCameraFPS();

	void processKeyboard(Camera_Movement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset,
		bool constrainPitch = true);
	void setViewMatrix();

	bool setMovementSpeed(float movementSpeed);
	float getMovementSpeed();
	bool setMouseSensitivity(float mouseSensitivity);
	float getMouseSensitivity();
	bool setZoom(float zoom);
	float getZoom();

private:

	// Camera Attributes
	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	// Eular Angles
	float _yaw;
	float _pitch;

	// Camera options
	float _movementSpeed;
	float _mouseSensitivity;
	float _zoom;

	void updateCameraVectors();
	float toRadians(float grados);
};

