#include "Game.h"
#include "VertexBufferLayout.h"

#include <fstream>
#include <ctime>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tinyobjloader-2.0-rc1/tiny_obj_loader.h"

Game::Game()
	: camera(new Camera(glm::vec3(0.f, 414.0f, 0.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f)))
{
	camFront = glm::vec3(0.f, 0.f, -1.f);
	fov = 90.0f;
	nearPlane = 0.1f;
	farPlane = 5000.f;

	firstMouse = true;

	m_Shader = new Shader("res/shaders/Basic.shader");
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

	map = new Map("res/models/buildings/buildings.obj", "res/textures/buildingTexture.jpg");
	character = new Character("res/models/finn.obj", "res/textures/tlo.jpg");
}
Game::~Game()
{	
}
void Game::OnUpdate(float deltaTime)
{
}
void Game::OnRender(Renderer* renderer)
{
	map->draw(camera, m_Shader, renderer, fov, nearPlane, farPlane);
	character->draw(camera, m_Shader, renderer, fov, nearPlane, farPlane);
}
void Game::Events(GLFWwindow* window)
{
	KeyboardEvents(window);
	MouseEvents(window);
	camera->updateInput(-1, mouseOffsetX, mouseOffsetY);
}
void Game::KeyboardEvents(GLFWwindow* window)
{	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->move(FORWARD);
		if (CheckForCollisions())
		{
			camera->move(BACKWARD);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->move(BACKWARD);
		if (CheckForCollisions())
		{
			camera->move(FORWARD);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->move(LEFT);
		if (CheckForCollisions())
		{
			camera->move(RIGHT);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->move(RIGHT);
		if (CheckForCollisions())
		{
			camera->move(LEFT);
		}
	}
}
void Game::MouseEvents(GLFWwindow* window)
{
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (firstMouse)
	{
		lastMouseX = mouseX;
		lastMouseY = mouseY;
		firstMouse = false;
	}

	//Calc offset
	mouseOffsetX = mouseX - lastMouseX;
	mouseOffsetY = lastMouseY - mouseY;

	//Set last X and Y
	lastMouseX = mouseX;
	lastMouseY = mouseY;
}
bool Game::CheckForCollisions()
{
	glm::vec4 area1a(-0.7f, -0.7f, -0.7f, -0.7f);
	glm::vec4 area1b(0.7f, 0.7f, 0.7f, 0.7f);
	glm::vec4 area2a(camera->getPosition(), 1.0f);
	glm::vec4 area2b(camera->getPosition(), 1.0f);

	if ( (((area1a.x <= area2a.x) && (area2a.x <= area1b.x)) ||
		((area1a.x <= area2b.x) && (area2b.x <= area1b.x))) &&

		(((area1a.y <= area2a.y) && (area2a.y <= area1b.y)) ||
		((area1a.y <= area2b.y) && (area2b.y <= area1b.y))) &&

			(((area1a.z <= area2a.z) && (area2a.z <= area1b.z)) ||
		((area1a.z <= area2b.z) && (area2b.z <= area1b.z))))
		return true;
	else
		return false;
}