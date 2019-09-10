#pragma once

#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"
#include "collisions.h"

#include <memory>

class Character
{
public:
	Character(string path, string texturePath, Camera* m_Camera);
	~Character();

	void draw(Shader* shader, Renderer* renderer, float fov, float nearPlane, float farPlane);
	std::vector <glm::vec3> getAreas();
	void follDown(Collision* collision);
	void jump();
private:
	VertexArray* characterVertexArray;
	VertexBuffer* characterVertexBuffer;
	std::unique_ptr<Texture> characterTexture;
	unsigned int characterVerticesCount;

	Camera* camera;
	float verticalSpeed;
};