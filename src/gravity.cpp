#include "gravity.h"

Gravity::Gravity(float acc)
{
	follDownAcc = acc;
	follDownSpeed = 0.f;
}

Gravity::~Gravity()
{
}

bool Gravity::characterFollDown(Camera* camera, Character* character, Collision* collision)
{
	if (camera->getPosition().y > -386.f)
	{
		follDownSpeed += follDownAcc;

		camera->setPosition(camera->getPosition() - glm::vec3(0.f, follDownSpeed, 0.f));
		collision->updateAreas2(character->getAreas());
		if (collision->isCollision())
		{
			camera->setPosition(camera->getPosition() + glm::vec3(0.f, follDownSpeed, 0.f));
			return 0;
		}
	}
	return 1;
}
