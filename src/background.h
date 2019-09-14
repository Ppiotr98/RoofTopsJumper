#pragma once

#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"

#include <memory>

class Background
{
public:
	Background(std::string texturePath);
	~Background();

	void draw(Camera* camera, Shader* shader, Renderer* renderer, float fov, float nearPlane, float farPlane);
private:
	GLuint va;
	GLuint vb;
	std::unique_ptr<Texture> texture;
};