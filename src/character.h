#pragma once

#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"

#include <memory>

class Character
{
public:
	Character(string path, string texturePath);
	~Character();

	void draw(Camera* camera, Shader* shader, Renderer* renderer, float fov, float nearPlane, float farPlane);
private:
	VertexArray* characterVertexArray;
	VertexBuffer* characterVertexBuffer;
	std::unique_ptr<Texture> characterTexture;

	unsigned int characterVerticesCount;
};