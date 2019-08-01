#pragma once
#include "Platform.h"
#include "Framework/Animation.h"

#define MOVING_PLATFORM_TIME_BETWEEN_CHANGE_DIRECTION 0.25f
#define MOVING_PLATFORM_VELOCITY_X 2

class MovingPlatform : public Platform
{
public:
	MovingPlatform(FLOAT WorldX, FLOAT WorldY, int Distance);
	~MovingPlatform();

	D3DXVECTOR2 GetVelocity() override;
	float GetVelocityX() override;
	float GetVelocityY() override;
	void Update(float dt) override;
	void Draw() override;
private:
	Animation *platform, *JetEngine;
	int FarLeft, FarRight;
	bool flag;
	int way, FrameCounter;
	float Timer;
};

