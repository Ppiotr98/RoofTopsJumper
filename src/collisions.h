#pragma once

#include <vector>

#include <glm/glm.hpp>

class Collision
{
public:
	Collision(std::vector <glm::vec3> m_Areas1, std::vector <glm::vec3> m_Areas2);
	~Collision();
	bool isCollision();
private:
	std::vector <glm::vec3> areas1;
	std::vector <glm::vec3> areas2;
};