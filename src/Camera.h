#pragma once

#include<iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
	glm::mat4 ViewMatrix;

	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat rotationX;
	GLfloat rotationY;

	void updateCameraVectors();

public:
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);
	~Camera() {}

	//Accessors
	const glm::mat4 getViewMatrix();
	const glm::vec3 getPosition() const;
	const glm::vec3 getRotation() const;
	const glm::vec3 getFront() const;
	const glm::vec3 getRight() const;
	const float getMovementSpeed() const;
	void setPosition(glm::vec3 position);

	//Functions
	void move(const int direction);
	void updateMouseInput(const double& offsetX, const double& offsetY);
	void updateInput(const int direction, const double& offsetX, const double& offsetY);
};