#include "Game.h"
#include "VertexBufferLayout.h"

#include <fstream>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tinyobjloader-2.0-rc1/tiny_obj_loader.h"

Game::Game()
	//: camera(glm::vec3(-2478.48f, 550.774f, 57.4234f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
	: camera(glm::vec3(-2476.39f, 440.31f, 70.2338f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f))
{
//	-2478.48f, 439.474f, 70.4234f
//	-2.09f, -0.836f, 0.1896f
	camFront = glm::vec3(0.f, 0.f, -1.f);
	fov = 90.0f;
	nearPlane = 0.1f;
	farPlane = 500.f;

	firstMouse = true;

	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	BuildingsVertexBuffer = new VertexBuffer("res/models/buildings/buildings.obj");
	BuildingsVerticesCount = BuildingsVertexBuffer->m_vertices.size() / 5;
	
	VertexBufferLayout BuildingsVertexLayout;
	BuildingsVertexLayout.Push<float>(3);
	BuildingsVertexLayout.Push<float>(2);

	BuildingsVertexArray = new VertexArray;
	BuildingsVertexArray->AddBuffer(BuildingsVertexBuffer, &BuildingsVertexLayout);
	
	m_Shader = new Shader("res/shaders/Basic.shader");
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
	BuildingsTexture = std::make_unique<Texture>("res/textures/roof.jpg");

	CharacterVertexBuffer = new VertexBuffer("res/models/finn.obj");
	CharacterVerticesCount = CharacterVertexBuffer->m_vertices.size() / 5;

	VertexBufferLayout CharacterVertexLayout;
	CharacterVertexLayout.Push<float>(3);
	CharacterVertexLayout.Push<float>(2);

	CharacterVertexArray = new VertexArray;
	CharacterVertexArray->AddBuffer(CharacterVertexBuffer, &CharacterVertexLayout);

	CharacterTexture = std::make_unique<Texture>("res/textures/tlo.jpg");
}
Game::~Game()
{	
}
void Game::OnUpdate(float deltaTime)
{
}
void Game::OnRender()
{
	Renderer renderer;

	glm::mat4 model1 = glm::mat4(1.0f);
	glm::mat4 view1 = camera.getViewMatrix();
	glm::mat4 projection1 = glm::mat4(1.0f);
	projection1 = glm::perspective(
		glm::radians(fov),
		800.0f / 600.0f,
		nearPlane, farPlane);
	glm::mat4 mvp1 = projection1 * view1 * model1;

	BuildingsTexture->Bind(0);
	m_Shader->SetUniform1i("u_Texture", 0);
	m_Shader->SetUniformMath4f("u_MVP", mvp1);

	renderer.Draw(BuildingsVertexArray, m_Shader, BuildingsVerticesCount);


	glm::mat4 model2 = glm::translate(glm::mat4(1.0f), camera.getPosition() + glm::vec3(-2.09f, -0.836f, 0.1896f));
	model2 = glm::scale(model2, glm::vec3(0.02f, 0.02f, 0.02f));
	model2 = glm::rotate(model2, 1.57f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view2 = camera.getViewMatrix();
	glm::mat4 projection2 = glm::mat4(1.0f);
	projection2 = glm::perspective(
		glm::radians(fov),
		800.0f / 600.0f,
		nearPlane, farPlane);
	glm::mat4 mvp2 = projection2 * view2 * model2;
	
	CharacterTexture->Bind(0);
	m_Shader->SetUniform1i("u_Texture", 0);
	m_Shader->SetUniformMath4f("u_MVP", mvp2);

	renderer.Draw(CharacterVertexArray, m_Shader, CharacterVerticesCount);
}
void Game::Events(GLFWwindow* window)
{
	KeyboardEvents(window);
	MouseEvents(window);
	camera.updateInput(-1, mouseOffsetX, mouseOffsetY);
}
void Game::KeyboardEvents(GLFWwindow* window)
{	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.move(FORWARD);
		if (CheckForCollisions())
		{
			camera.move(BACKWARD);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.move(BACKWARD);
		if (CheckForCollisions())
		{
			camera.move(FORWARD);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.move(LEFT);
		if (CheckForCollisions())
		{
			camera.move(RIGHT);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.move(RIGHT);
		if (CheckForCollisions())
		{
			camera.move(LEFT);
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
	glm::vec4 area2a(camera.getPosition(), 1.0f);
	glm::vec4 area2b(camera.getPosition(), 1.0f);

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