#pragma once

#include "Camera.h"
#include "VertexBuffer.h"
#include "collisions.h"
#include "character.h"

#include <vector>

class Gravity
{
public:
	Gravity(float speed);
	~Gravity();
	bool characterFollDown(Camera* camera, Character* character, Collision* collision);
private:
	float follDownAcc;
	float follDownSpeed;
};