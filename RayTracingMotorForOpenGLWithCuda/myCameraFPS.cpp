#include "myCameraFPS.h"

myCameraFPS::myCameraFPS(glm::vec3 position, glm::vec3 up, float yaw, float pitch){
	this->_front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->_movementSpeed = SPEED;
	this->_mouseSensitivity = SENSITIVTY;

	this->_zoom = ZOOM;
	this->_position = position;
	this->_worldUp = up;
	this->_yaw = yaw;
	this->_pitch = pitch;
	this->updateCameraVectors();
}

myCameraFPS::~myCameraFPS()
{
}

void myCameraFPS::processKeyboard(Camera_Movement direction, float deltaTime) {
	float velocity = this->_movementSpeed * deltaTime;
	
	switch (direction)
	{
	case C_FORWARD:
		this->_position += this->_front * velocity;
		break;
	case C_BACKWARD:
		this->_position -= this->_front * velocity;
		break;
	case C_LEFT:
		this->_position -= glm::normalize(glm::cross(this->_front, this->_up)) * velocity;
		break;
	case C_RIGHT:
		this->_position += glm::normalize(glm::cross(this->_front, this->_up)) * velocity;
		break;
	default:
		break;
	}
}

void myCameraFPS::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
	xoffset *= this->_mouseSensitivity;
	yoffset *= this->_mouseSensitivity;

	this->_yaw += xoffset;
	this->_pitch += yoffset;

	if (constrainPitch) {
		if (this->_pitch > 89.0f) {
			this->_pitch = 89.0f;
		}
		if (this->_pitch < -89.0f) {
			this->_pitch = -89.0f;
		}
	}

	this->updateCameraVectors();
}

void myCameraFPS::setViewMatrix() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		this->_position.x, this->_position.y, this->_position.z, 
			this->_position.x + this->_front.x,
			this->_position.y + this->_front.y,
			this->_position.z + this->_front.z,
		this->_up.x, this->_up.y, this->_up.z);
}

bool myCameraFPS::setMovementSpeed(float movementSpeed){
	this->_movementSpeed = movementSpeed;
	return true;
}

float myCameraFPS::getMovementSpeed(){
	return this->_movementSpeed;
}

bool myCameraFPS::setMouseSensitivity(float mouseSensitivity){
	this->_mouseSensitivity = mouseSensitivity;
	return true;
}

float myCameraFPS::getMouseSensitivity(){
	return this->_mouseSensitivity;
}

bool myCameraFPS::setZoom(float zoom){
	this->_zoom = zoom;
	return false;
}

float myCameraFPS::getZoom(){
	return this->_zoom;
}

void myCameraFPS::updateCameraVectors() {
	glm::vec3 front;
	front.x = cos(toRadians(this->_yaw)) * cos(toRadians(this->_pitch));
	front.y = sin(toRadians(this->_pitch));
	front.z = sin(toRadians(this->_yaw)) * cos(toRadians(this->_pitch));
	this->_front = glm::normalize(front);
	this->_right = glm::normalize(glm::cross(this->_front, this->_worldUp));
	this->_up = glm::normalize( glm::cross(this->_right, this->_front) );
}

float myCameraFPS::toRadians(float grados) {
	return grados * M_PI / 180.0f;
}
