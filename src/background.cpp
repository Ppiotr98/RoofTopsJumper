#include "background.h"
#include "Renderer.h"

#include <ctime>

Background::Background(std::string texturePath)
{
	float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f, //0
			 50.0f, -50.0f, 1.0f, 0.0f, //1
			 50.0f,  50.0f, 1.0f, 1.0f, //2
			 50.0f,  50.0f, 1.0f, 1.0f, //2
			-50.0f,  50.0f, 0.0f, 1.0f, //3
			-50.0f, -50.0f, 0.0f, 0.0f, //0
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, 4 * 6 * sizeof(float), &positions[0], GL_STATIC_DRAW);
	
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);

	glBindVertexArray(va);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

	texture = std::make_unique<Texture>(texturePath);
}

Background::~Background()
{
}
void Background::draw(Camera* camera, Shader* shader, Renderer* renderer, float fov, float nearPlane, float farPlane)
{
	glm::mat4 mvp = glm::mat4(1.f);

	texture->Bind();
	shader->SetUniform1i("u_Texture", 0);
	shader->SetUniformMath4f("u_MVP", mvp);

	shader->Bind();
	glBindVertexArray(va);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}