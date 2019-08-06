#pragma once
#include "Platform.h"
#include "Framework/Animation.h"
#define CROSS_PLATFORM_TIME_BETWEEN_CHANGE_DIRECTION 0.5f
#define CROSS_PLATFORM_VELOCITY 0.75f

class CrossPlatform : public Platform
{
public:
	CrossPlatform(FLOAT WorldX, FLOAT WorldY, int Distance);
	~CrossPlatform();
	D3DXVECTOR2 GetVelocity() override;
	float GetVelocityX() override;
	float GetVelocityY() override;
	void Update(float dt) override;
	void Draw() override;
private:
	Animation *platform;
	Animation *JetEngineHorizontal;
	Animation *JetEngineVertical;
	int From;
	int To;
	int way;
	int FrameCounter;
	float Timer;
	bool flag;
};

