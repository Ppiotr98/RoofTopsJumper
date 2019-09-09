#pragma once

#include <vector>

#include <glm/glm.hpp>

class Collision
{
public:
	Collision(std::vector <glm::vec3> m_Areas1, std::vector <glm::vec3> m_Areas2);
	~Collision();
	bool isCollision();
	void updateAreas1(std::vector <glm::vec3> newAreas);
	void updateAreas2(std::vector <glm::vec3> newAreas);
private:
	std::vector <glm::vec3> areas1;
	std::vector <glm::vec3> areas2;
};