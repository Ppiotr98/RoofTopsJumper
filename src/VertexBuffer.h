#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <string>

class VertexBuffer
{

public:
	GLuint m_RendererID;

	std::vector <float> m_vertices;

	VertexBuffer(std::string path);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};
