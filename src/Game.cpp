#include "Game.h"
#include "VertexBufferLayout.h"
#include "collisions.h"

#include <fstream>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader-2.0-rc1/tiny_obj_loader.h"

Game::Game()
	: camera(new Camera(glm::vec3(0.f, 414.0f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f)))
{
	camFront = glm::vec3(0.f, 0.f, -1.f);
	fov = 90.0f;
	nearPlane = 0.1f;
	farPlane = 5000.f;

	m_Shader = new Shader("res/shaders/Basic.shader");
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

//	background = new Background("res/textures/background.jpg");
	map = new Map("res/models/buildings/buildings.obj", "res/textures/buildingTexture.jpg");
	character = new Character("res/models/finn.obj", "res/textures/tlo.jpg", camera);

	collision = new Collision(map->getAreas(), character->getAreas());
}
Game::~Game()
{	
}
void Game::OnUpdate(float deltaTime)
{
}
void Game::OnRender(Renderer* renderer)
{
//	background->draw(camera, m_Shader, renderer, fov, nearPlane, farPlane);
	map->draw(camera, m_Shader, renderer, fov, nearPlane, farPlane);
	character->draw(m_Shader, renderer, fov, nearPlane, farPlane);
}
void Game::Events(GLFWwindow* window)
{
	KeyboardEvents(window);
	MouseEvents(window);
	character->follDown(collision);
	camera->updateInput(-1, mouseOffsetX, mouseOffsetY);
}
void Game::KeyboardEvents(GLFWwindow* window)
{	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		character->move(2, collision);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		character->move(-2, collision);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		character->move(-1, collision);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		character->move(1, collision);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		character->jump();
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		camera->setPosition(glm::vec3(0.f, 414.0f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		exit(1);
	}
}
void Game::MouseEvents(GLFWwindow* window)
{
	glfwGetCursorPos(window, &mouseX, &mouseY);

	//Calc offset
	mouseOffsetX = mouseX - 960;
	mouseOffsetY = 540 - mouseY;

	glfwSetCursorPos(window, 960, 540);
}