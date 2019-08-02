#include "ElectricShockwaveBarrier.h"

int ElectricShockwaveBarrier::ID = -1;

ElectricShockwaveBarrier::ElectricShockwaveBarrier(int WorldX, int WorldY) : Entity()
{
	Entity::position.x = WorldX;
	Entity::position.y = WorldY;
}

ElectricShockwaveBarrier::~ElectricShockwaveBarrier()
{
}
