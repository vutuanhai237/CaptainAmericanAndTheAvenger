#include "Platform.h"

int Platform::DisappearPlatformID = -1;
int Platform::MovingPlatformID = -1;
int Platform::JetEngineVerticalID = -1;
int Platform::JetEngineHorizontalID = -1;

Platform::Platform(FLOAT WorldX, FLOAT WorldY) : Entity()
{
	Entity::type = Entity::Entity_Type::platform;
	Entity::position.x = WorldX;
	Entity::position.y = WorldY;
}

Platform::~Platform()
{
}