#include "CirclePlatform.h"
#include "Framework/GameSetting.h"

CirclePlatform::CirclePlatform(FLOAT WorldX, FLOAT WorldY, FLOAT Width, FLOAT Height, FLOAT Period) : Platform(WorldX, WorldY)
{
	Entity::tag = Entity::Entity_Tag::circle_platform;
	platform = new Animation(Platform::MovingPlatformID, 1);
	platform->Stop(); 
	JetEngineHorizontal = new Animation(Platform::JetEngineHorizontalID, 1);
	JetEngineHorizontal->Stop();
	JetEngineVertical = new Animation(Platform::JetEngineVerticalID, 1);
	JetEngineVertical->Stop();
	Ax = Width;
	Ay = Height;
	omega = 2 * PI / Period;
	t = 0;
	this->Update(0);
}

CirclePlatform::~CirclePlatform()
{
	delete platform;
	delete JetEngineHorizontal;
	delete JetEngineVertical;
}

D3DXVECTOR2 CirclePlatform::GetPosition()
{
	return DrawPoint;
}

D3DXVECTOR2 CirclePlatform::GetVelocity()
{
	return D3DXVECTOR2(deltaX, deltaY);
}

float CirclePlatform::GetVelocityX()
{
	return deltaX;
}

float CirclePlatform::GetVelocityY()
{
	return deltaY;
}

BoundingBox CirclePlatform::GetBoundingBox()
{
	return BoundingBox(DrawPoint, Entity::size, 0, 0);
}

void CirclePlatform::Update(float dt)
{
	FrameCounter++;
	t -= dt;
	deltaX = Ax * cos(omega*t + PI / 2) - VirtualPoint.x;
	deltaY = Ay * cos(omega*t) - VirtualPoint.y;
	VirtualPoint.x += deltaX;
	VirtualPoint.y += deltaY;
	DrawPoint.x = Entity::position.x + VirtualPoint.x;
	DrawPoint.y = Entity::position.y + VirtualPoint.y;
	JetEngineHorizontal->SetScale((FLOAT)(deltaX > 0 ? 1 : -1), (FLOAT)1);
}

void CirclePlatform::Draw()
{
	platform->Draw(DrawPoint);
	if (FrameCounter >> 2 & 1)
	{
		if (abs(deltaX) < 0.25f || abs(deltaY) < 0.25f)
		{
			return;
		}
		JetEngineHorizontal->Draw(DrawPoint.x + 20 * (deltaX < 0 ? 1 : -1), DrawPoint.y);
		JetEngineVertical->Draw(DrawPoint.x - 8, DrawPoint.y - 13);
		JetEngineVertical->Draw(DrawPoint.x + 8, DrawPoint.y - 13);
	}
}
