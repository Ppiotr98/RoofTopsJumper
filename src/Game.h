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
	bool loadOBJ(const char* path, std::vector < glm::vec3 >* out_vertices, std::vector < glm::vec2 >* out_uvs, std::vector < glm::vec3 >* out_normals);
private:
	VertexArray* m_VAO;
	VertexBuffer* m_VertexBuffer;
	VertexBuffer* m_UvBuffer;
	VertexBuffer* m_NormalBuffer;
	std::unique_ptr<Shader> m_IndexBuffer;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<Texture> m_Texture1;
	std::unique_ptr<Texture> m_Texture2;

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;

	unsigned int verticesCount;

	glm::mat4 m_Proj, m_View;

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