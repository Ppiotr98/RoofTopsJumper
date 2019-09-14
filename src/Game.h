#pragma once

#include "Texture.h"
#include "Camera.h"
#include "map.h"
#include "character.h"
#include "background.h"

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

	Background* background;
	Map* map;
	Character* character;

	Collision* collision;

	Camera* camera;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;
	float fov = 90.0f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;

	double mouseX = 0.0;
	double mouseY = 0.0;
	double mouseOffsetX = 0.0;
	double mouseOffsetY = 0.0;
};