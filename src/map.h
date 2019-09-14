#pragma once

#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"

#include <memory>

class Map
{
public:
	Map(std::string path, std::string texturePath);
	~Map();

	std::vector <glm::vec3> createTranslations();
	void draw(Camera* camera, Shader* shader, Renderer* renderer, float fov, float nearPlane, float farPlane);
	std::vector <glm::vec3> getAreas();
private:
	VertexArray* BuildingsVertexArray;
	VertexBuffer* BuildingsVertexBuffer;
	std::unique_ptr<Texture> BuildingsTexture;

	unsigned int BuildingsVerticesCount;

	std::vector <glm::vec3> buildingsTranslations;
};