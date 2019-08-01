#include "CrossPlatform.h"

CrossPlatform::CrossPlatform(FLOAT WorldX, FLOAT WorldY, int Distance) : Platform(WorldX, WorldY)
{
	Entity::tag = Entity::Entity_Tag::cross_platform;
	platform = new Animation(Platform::MovingPlatformID, 1);
	platform->Stop();
	JetEngineHorizontal = new Animation(Platform::JetEngineHorizontalID, 1);
	JetEngineHorizontal->Stop();
	JetEngineVertical = new Animation(Platform::JetEngineVerticalID, 1);
	JetEngineVertical->Stop();
	From = WorldX;
	To = WorldX + Distance; 
	flag = false;
	way = -1;
	Timer = 0;
	FrameCounter = 0;
}

CrossPlatform::~CrossPlatform()
{
	delete platform;
	delete JetEngineHorizontal;
	delete JetEngineVertical;
}

D3DXVECTOR2 CrossPlatform::GetVelocity()
{
	return D3DXVECTOR2(this->GetVelocityX(), this->GetVelocityY());
}

float CrossPlatform::GetVelocityX()
{
	return CROSS_PLATFORM_VELOCITY * way*(flag ? 0 : 1);
}

float CrossPlatform::GetVelocityY()
{
	return CROSS_PLATFORM_VELOCITY * way*(flag ? 0 : 1);
}

void CrossPlatform::Update(float dt)
{
	FrameCounter++;
	if (flag)
	{
		Timer += dt;
		if (Timer >= CROSS_PLATFORM_TIME_BETWEEN_CHANGE_DIRECTION)
		{
			Timer = 0;
			way = way * -1;
			Entity::position.x += CROSS_PLATFORM_VELOCITY * way;
			Entity::position.y += CROSS_PLATFORM_VELOCITY * way;
			flag = false;
			FrameCounter = 0;
		}
	}
	else
	{
		if (From < Entity::position.x && Entity::position.x < To)
		{
			Entity::position.x += CROSS_PLATFORM_VELOCITY * way;
			Entity::position.y += CROSS_PLATFORM_VELOCITY * way;
		}
		else
			flag = true;
	}
	JetEngineHorizontal->SetScale(way, 1);
}

void CrossPlatform::Draw()
{
	platform->Draw(Entity::position);
	if (!flag && FrameCounter >> 2 & 1)
	{
		JetEngineHorizontal->Draw(Entity::position.x + 20 * (-way), Entity::position.y);
		JetEngineVertical->Draw(Entity::position.x - 8, Entity::position.y - 13);
		JetEngineVertical->Draw(Entity::position.x + 8, Entity::position.y - 13);
	}
}