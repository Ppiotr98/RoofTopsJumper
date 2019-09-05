#pragma once

#include "Texture.h"
#include "Camera.h"

class Game
{
public:
	Game();
	~Game();

	void OnUpdate(float deltaTime);
	void OnRender();
	void Events(GLFWwindow* window);
	void KeyboardEvents(GLFWwindow* window);
	void MouseEvents(GLFWwindow* window);
	bool CheckForCollisions();
private:
	VertexArray* BuildingsVertexArray;
	VertexArray* CharacterVertexArray;
	VertexBuffer* BuildingsVertexBuffer;
	VertexBuffer* CharacterVertexBuffer;
	Shader* m_Shader;
	std::unique_ptr<Texture> BuildingsTexture;
	std::unique_ptr<Texture> CharacterTexture;

	unsigned int BuildingsVerticesCount;
	unsigned int CharacterVerticesCount;

	double lastMouseX = 0.0;
	double lastMouseY = 0.0;
	double mouseX = 0.0;
	double mouseY = 0.0;
	double mouseOffsetX = 0.0;
	double mouseOffsetY = 0.0;
	bool firstMouse = true;

	Camera camera;

	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

	float fov = 90.0f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;
};