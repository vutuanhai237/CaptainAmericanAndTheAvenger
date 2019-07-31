#pragma once
#include "Platform.h"
#include "Framework/Animation.h"

#define DISAPPEAR_PLATFORM_TIME_SPLIT 1.5f
#define DISAPPEAR_PLATFORM_TIME_COMEBACK 1.5f
#define DISAPPEAR_PLATFORM_TIME_FIRST_DISAPPEAR 1.0f

class DisappearPlatform : public Platform
{
public:
	DisappearPlatform(FLOAT WorldX, FLOAT WorldY);
	~DisappearPlatform() override;

	BoundingBox GetBoundingBox() override;
	int OnCollision(Entity *, float dt) override;
	void Update(float dt) override;
	void Draw() override;
private:
	Animation *Left, *Right;
	D3DXVECTOR2 Lpos, Rpos;
	bool IsSplit;
	bool Started;
	float Timer;
	int FrameCounter;
	int MoveFlag;
};

