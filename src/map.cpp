#include "map.h"
#include "Renderer.h"

#include <ctime>

Map::Map(string modelPath, string texturePath)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	BuildingsVertexBuffer = new VertexBuffer("res/models/cube.obj");
	BuildingsVerticesCount = BuildingsVertexBuffer->m_vertices.size() / 5;

	VertexBufferLayout BuildingsVertexLayout;
	BuildingsVertexLayout.Push<float>(3);
	BuildingsVertexLayout.Push<float>(2);

	BuildingsVertexArray = new VertexArray;
	BuildingsVertexArray->AddBuffer(BuildingsVertexBuffer, &BuildingsVertexLayout);

	BuildingsTexture = std::make_unique<Texture>("res/textures/buildingTexture.jpg");

	buildingsTranslations = createTranslations();
}

Map::~Map()
{
}

vector <glm::vec3> Map::createTranslations()
{
	unsigned int lastDirection_2 = 1;
	unsigned int lastDirection_1 = 1;
	glm::vec3 lastTranslation_1(400.f, 0.f, 0.f);
	buildingsTranslations.push_back(glm::vec3(0.f, 0.f, 0.f));
	buildingsTranslations.push_back(lastTranslation_1);
	srand(time(NULL));
	for (int i = 2; i < 100; i++)
	{
		unsigned int currentDirection = rand() % 3;
		glm::vec3 currentTranslation;
		switch (currentDirection)
		{
		case 0: //left
			if (lastDirection_1 == 2 || lastDirection_2 == 2)
				currentTranslation = lastTranslation_1 + glm::vec3(400.f, 0.f, 0.f);
			else
				currentTranslation = lastTranslation_1 + glm::vec3(0.f, 0.f, -400.f);
			break;
		case 1: //forward
			currentTranslation = lastTranslation_1 + glm::vec3(400.f, 0.f, 0.f);
			break;
		case 2: //right
			if (lastDirection_1 == 0 || lastDirection_2 == 0)
				currentTranslation = lastTranslation_1 + glm::vec3(400.f, 0.f, 0.f);
			else
				currentTranslation = lastTranslation_1 + glm::vec3(0.f, 0.f, 400.f);
			break;
		}

		unsigned int currentHighDirection = rand() % 3;
		static unsigned int highJump = 30;
		switch (currentHighDirection)
		{
		case 0: //down
			if(currentTranslation.y > -600)
				currentTranslation.y -= highJump;
			break;
		case 1: //sameLevel
			break;
		case 2: //up
			currentTranslation.y += highJump;
			break;
		}

		buildingsTranslations.push_back(currentTranslation);
		lastDirection_2 = lastDirection_1;
		lastDirection_1 = currentDirection;
		lastTranslation_1 = currentTranslation;
	}

	return buildingsTranslations;
}

void Map::draw(Camera* camera, Shader* shader, Renderer* renderer, float fov, float nearPlane, float farPlane)
{
	glm::mat4 view1 = camera->getViewMatrix();
	glm::mat4 projection1 = glm::mat4(1.0f);
	projection1 = glm::perspective(
		glm::radians(fov),
		1920.0f / 1080.0f,
		nearPlane, farPlane);

	BuildingsTexture->Bind(0);
	shader->SetUniform1i("u_Texture", 0);

	glm::mat4 mvp1;
	glm::mat4 model1;
	for (int i = 0; i < 100; i++)
	{
		model1 = glm::translate(glm::mat4(1.f), buildingsTranslations[i]);
		model1 = glm::scale(model1, glm::vec3(300.0f, 800.0f, 300.0f));
		mvp1 = projection1 * view1 * model1;
		shader->SetUniformMath4f("u_MVP", mvp1);
		renderer->Draw(BuildingsVertexArray, shader, BuildingsVerticesCount);
	}
}