#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(FLOAT WorldX, FLOAT WorldY, int Distance) : Platform(WorldX, WorldY)
{
	Entity::tag = Entity::Entity_Tag::moving_platform;
	platform = new Animation(Platform::MovingPlatformID, 1);
	platform->Stop();
	JetEngine = new Animation(Platform::JetEngineHorizontalID, 1);
	JetEngine->Stop();
	FarLeft = WorldX - Distance / 2;
	FarRight = WorldX + Distance / 2;
	flag = false;
	way = 1;
	Timer = 0;
	FrameCounter = 0;
}

MovingPlatform::~MovingPlatform()
{
	delete platform;
	delete JetEngine;
}

D3DXVECTOR2 MovingPlatform::GetVelocity()
{
	return D3DXVECTOR2(MOVING_PLATFORM_VELOCITY_X*way*(flag ? 0 : 1), 0);
}

float MovingPlatform::GetVelocityX()
{
	return MOVING_PLATFORM_VELOCITY_X * way*(flag ? 0 : 1);
}

float MovingPlatform::GetVelocityY()
{
	return 0.0f;
}

void MovingPlatform::Update(float dt)
{
	FrameCounter++;
	if (flag)
	{
		Timer += dt;
		if (Timer >= MOVING_PLATFORM_TIME_BETWEEN_CHANGE_DIRECTION)
		{
			Timer = 0;
			way = way * -1;
			Entity::position.x += MOVING_PLATFORM_VELOCITY_X * way;
			flag = false;
			FrameCounter = 0;
		}
	} 
	else
	{
		if (FarLeft < Entity::position.x && Entity::position.x < FarRight)
			Entity::position.x += MOVING_PLATFORM_VELOCITY_X * way;
		else
			flag = true;
	}
	JetEngine->SetScale(way, 1);
}

void MovingPlatform::Draw()
{
	platform->DrawInt(Entity::position);
	if (!flag && FrameCounter >> 2 & 1)
		JetEngine->DrawInt(Entity::position.x + 20 * (-way), Entity::position.y);
}
