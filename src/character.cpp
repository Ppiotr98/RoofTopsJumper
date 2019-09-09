#include "character.h"
#include "Renderer.h"

#include <ctime>

Character::Character(string modelPath, string texturePath)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	characterVertexBuffer = new VertexBuffer(modelPath);
	characterVerticesCount = characterVertexBuffer->m_vertices.size() / 5;

	VertexBufferLayout characterVertexLayout;
	characterVertexLayout.Push<float>(3);
	characterVertexLayout.Push<float>(2);

	characterVertexArray = new VertexArray;
	characterVertexArray->AddBuffer(characterVertexBuffer, &characterVertexLayout);

	characterTexture = std::make_unique<Texture>(texturePath);
}

Character::~Character()
{
}

void Character::draw(Camera* camera, Shader* shader, Renderer* renderer, float fov, float nearPlane, float farPlane)
{
	float distance = -2.5f;
	float dz = distance * sin(glm::radians(camera->getRotation().y));
	float dx = distance * (cos(glm::radians(camera->getRotation().y)) - 1);
	glm::mat4 model2 = glm::translate(glm::mat4(1.0f), camera->getPosition() + glm::vec3(distance + dx, -0.836f, dz));
	model2 = glm::scale(model2, glm::vec3(0.02f, 0.02f, 0.02f));
	model2 = glm::rotate(model2, 1.57f - glm::radians(camera->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view2 = camera->getViewMatrix();
	glm::mat4 projection2 = glm::mat4(1.0f);
	projection2 = glm::perspective(
		glm::radians(fov),
		1920.0f / 1080.0f,
		nearPlane, farPlane);
	glm::mat4 mvp2 = projection2 * view2 * model2;

	characterTexture->Bind();
	shader->SetUniform1i("u_Texture", 0);
	shader->SetUniformMath4f("u_MVP", mvp2);

	renderer->Draw(characterVertexArray, shader, characterVerticesCount);
}