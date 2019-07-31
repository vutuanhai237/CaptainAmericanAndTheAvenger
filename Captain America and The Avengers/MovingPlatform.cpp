#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(FLOAT WorldX, FLOAT WorldY, int Distance) : Platform(WorldX, WorldY)
{
	Entity::tag = Entity::Entity_Tag::moving_platform;
	Entity::size.cx = 32;
	Entity::size.cy = 16;
	platform = new Animation(Platform::MovingPlatformID, 1);
	platform->Stop();
	JetEngine = new Animation(Platform::JetEngineHorizontalID, 1);
	JetEngine->Stop();
	FarLeft = WorldX - Distance / 2;
	FarRight = WorldX + Distance * 2;
	Direction = 1;
}

MovingPlatform::~MovingPlatform()
{
	delete platform;
	delete JetEngine;
}

BoundingBox MovingPlatform::GetBoundingBox()
{
	return BoundingBox(D3DXVECTOR2(position.x, position.y - 8), size, 0, 0);
}

int MovingPlatform::OnCollision(Entity *, float dt)
{
	return 0;
}

void MovingPlatform::Update(float dt)
{
}

void MovingPlatform::Draw()
{
	platform->Draw(Entity::position);

}
