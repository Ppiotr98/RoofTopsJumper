#include "character.h"
#include "Renderer.h"

Character::Character(std::string modelPath, std::string texturePath, Camera* m_Camera)
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

	camera = m_Camera;
	verticalSpeed = 0.f;
}

Character::~Character()
{
}

void Character::draw(Shader* shader, Renderer* renderer, float fov, float nearPlane, float farPlane)
{
	glm::mat4 mvp = getMVP(fov, nearPlane, farPlane);

	characterTexture->Bind();
	shader->SetUniform1i("u_Texture", 0);
	shader->SetUniformMath4f("u_MVP", mvp);

	renderer->Draw(characterVertexArray, shader, characterVerticesCount);
}

glm::mat4 Character::getMVP(float fov, float nearPlane, float farPlane)
{
	float distance = -2.5f;
	float dz = distance * sin(glm::radians(camera->getRotation().y));
	float dx = distance * (cos(glm::radians(camera->getRotation().y)) - 1);
	glm::mat4 model = glm::translate(glm::mat4(1.0f), camera->getPosition() + glm::vec3(distance + dx, -0.836f, dz));
	model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
	model = glm::rotate(model, 1.57f - glm::radians(camera->getRotation().y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(
		glm::radians(fov),
		1920.0f / 1080.0f,
		nearPlane, farPlane);
	glm::mat4 mvp = projection * view * model;
	return mvp;
}

std::vector <glm::vec3> Character::getAreas()
{
	std::vector <glm::vec3> ans = {};
	ans.push_back(camera->getPosition() - glm::vec3(3.f, 14.f, 5.f));
	ans.push_back(camera->getPosition() + glm::vec3(3.f, 3.f, 5.f));
	return ans;
}

void Character::follDown(Collision* collision)
{
	if (camera->getPosition().y > -386.f)
	{
		verticalSpeed -= 0.03f;

		camera->setPosition(camera->getPosition() + glm::vec3(0.f, verticalSpeed, 0.f));
		collision->updateAreas2(getAreas());
		if (collision->isCollision())
		{
			camera->setPosition(camera->getPosition() - glm::vec3(0.f, verticalSpeed, 0.f));
			verticalSpeed = 0.f;
		}
	}
}

void Character::jump()
{
	if(verticalSpeed == 0.f)
		verticalSpeed += 1.5f;
}

void Character::move(const int direction, Collision* collision)
{
	camera->move(direction);
	collision->updateAreas2(getAreas());
	if (collision->isCollision())
	{
		camera->move(-direction);
	}
}
