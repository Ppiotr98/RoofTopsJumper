#pragma once

#include "VertexArray.h"
#include "Texture.h"
#include "Camera.h"
#include "collisions.h"

#include <memory>

class Character
{
public:
	Character(std::string path, std::string texturePath, Camera* m_Camera);
	~Character();

	void draw(Shader* shader, Renderer* renderer, float fov, float nearPlane, float farPlane);
	std::vector <glm::vec3> getAreas();
	void follDown(Collision* collision);
	void jump();
	void move(const int direction, Collision* collision);
private:
	VertexArray* characterVertexArray;
	VertexBuffer* characterVertexBuffer;
	std::unique_ptr<Texture> characterTexture;
	unsigned int characterVerticesCount;

	Camera* camera;
	float verticalSpeed;

	glm::mat4 getMVP(float fov, float nearPlane, float farPlane);
};