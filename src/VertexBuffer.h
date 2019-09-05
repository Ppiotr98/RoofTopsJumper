#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <string>

using namespace std;

class VertexBuffer
{

public:
	GLuint m_RendererID;

	vector <float> m_vertices;

	VertexBuffer(string path);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};
