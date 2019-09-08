#pragma once

#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"

#include <memory>

class Map
{
public:
	Map(string path, string texturePath);
	~Map();

	vector <glm::vec3> createTranslations();
	void draw(Camera* camera, Shader* shader, Renderer* renderer, float fov, float nearPlane, float farPlane);
private:
	VertexArray* BuildingsVertexArray;
	VertexBuffer* BuildingsVertexBuffer;
	std::unique_ptr<Texture> BuildingsTexture;

	unsigned int BuildingsVerticesCount;

	vector <glm::vec3> buildingsTranslations;
};