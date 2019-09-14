#include "Renderer.h"

#include <iostream>

using namespace std;

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << endl;
		return false;
	}
	return true;
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray* va, const Shader* shader, const unsigned int count) const
{
	shader->Bind();
	va->Bind();
	glDrawArrays(GL_TRIANGLES, 0, count);
}
