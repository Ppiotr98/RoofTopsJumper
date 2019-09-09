#include "collisions.h"

Collision::Collision(std::vector <glm::vec3> m_Areas1, std::vector <glm::vec3> m_Areas2)
{
	areas1 = m_Areas1;
	areas2 = m_Areas2;
}

Collision::~Collision()
{
}

bool Collision::isCollision()
{
	glm::vec3 object1vertex1;
	glm::vec3 object1vertex2;
	glm::vec3 object2vertex1;
	glm::vec3 object2vertex2;
	for (int i = 0; i < areas1.size(); i += 2)
	{
		object1vertex1 = areas1[i];
		object1vertex2 = areas1[i + 1];
		for (int j = 0; j < areas2.size(); j += 2)
		{
			object2vertex1 = areas2[j];
			object2vertex2 = areas2[j + 1];
			if ((((object1vertex1.x < object2vertex1.x) && (object2vertex1.x < object1vertex2.x)) ||
				((object1vertex1.x < object2vertex2.x) && (object2vertex2.x < object1vertex2.x))) &&

				(((object1vertex1.y < object2vertex1.y) && (object2vertex1.y < object1vertex2.y)) ||
				((object1vertex1.y < object2vertex2.y) && (object2vertex2.y < object1vertex2.y))) &&

					(((object1vertex1.z < object2vertex1.z) && (object2vertex1.z < object1vertex2.z)) ||
				((object1vertex1.z < object2vertex2.z) && (object2vertex2.z < object1vertex2.z))))
				return true;
		}
	}
	return false;
}

void Collision::updateAreas1(std::vector<glm::vec3> newAreas)
{
	areas1 = newAreas;
}

void Collision::updateAreas2(std::vector<glm::vec3> newAreas)
{
	areas2 = newAreas;
}
