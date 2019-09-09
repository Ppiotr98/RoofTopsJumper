#pragma once

#include "Texture.h"
#include "Camera.h"
#include "map.h"
#include "character.h"

class Game
{
public:
	Game();
	~Game();

	void OnUpdate(float deltaTime);
	void OnRender(Renderer* renderer);
	void Events(GLFWwindow* window);
	void KeyboardEvents(GLFWwindow* window);
	void MouseEvents(GLFWwindow* window);
private:
	Shader* m_Shader;

	Camera* camera;

	double lastMouseX = 0.0;
	double lastMouseY = 0.0;
	double mouseX = 0.0;
	double mouseY = 0.0;
	double mouseOffsetX = 0.0;
	double mouseOffsetY = 0.0;
	bool firstMouse = true;

	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	float fov = 90.0f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;

	Map* map;
	Character* character;
};