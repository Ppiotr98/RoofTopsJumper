#include "Camera.h"

void Camera::updateCameraVectors()
{
	this->front.x = cos(glm::radians(this->rotationY)) * cos(glm::radians(this->rotationX));
	this->front.y = sin(glm::radians(this->rotationX));
	this->front.z = sin(glm::radians(this->rotationY)) * cos(glm::radians(this->rotationX));

	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
{
	this->ViewMatrix = glm::mat4(1.f);

	this->movementSpeed = 2.0f;
	this->sensitivity = 0.5f;

	this->worldUp = worldUp;
	this->position = position;
	this->right = glm::vec3(0.0f);
	this->up = worldUp;

	this->rotationX = -26.0f;
	this->rotationY = 0.0f;
	this->rotationDis = 0.0f;

	this->updateCameraVectors();
}

const glm::mat4 Camera::getViewMatrix()
{
	this->updateCameraVectors();

	this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

	return this->ViewMatrix;
}

const glm::vec3 Camera::getPosition() const
{
	return this->position;
}

const glm::vec3 Camera::getRotation() const
{
	return glm::vec3(rotationX, rotationY, rotationDis);
}

void Camera::setPosition(glm::vec3 newPosition)
{
	this->position = newPosition;
}

void Camera::move(const int direction)
{
	//Update position vector
	switch (direction)
	{
	case FORWARD:
		this->position += this->front * this->movementSpeed;
		break;
	case BACKWARD:
		this->position -= this->front * this->movementSpeed;
		break;
	case LEFT:
		this->position -= this->right * this->movementSpeed;
		break;
	case RIGHT:
		this->position += this->right * this->movementSpeed;
		break;
	default:
		break;
	}
}

void Camera::updateMouseInput(const double& offsetX, const double& offsetY)
{
	//Update pitch yaw and roll
	this->rotationX += static_cast<GLfloat>(offsetY) * this->sensitivity;
	this->rotationY += static_cast<GLfloat>(offsetX) * this->sensitivity;

	if (this->rotationX > 90.0f)
		this->rotationX = 90.0f;
	else if (this->rotationX < -90.0f)
		this->rotationX = -90.0f;

	if (this->rotationY > 360.0f || this->rotationY < -360.0f)
		this->rotationY = 0.0f;
}

void Camera::updateInput(const int direction, const double& offsetX, const double& offsetY)
{
	this->updateMouseInput(offsetX, offsetY);
}