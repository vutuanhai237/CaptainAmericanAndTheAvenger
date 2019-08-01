#pragma once
#include "Platform.h"
#include "Framework/Animation.h"

class CirclePlatform : public Platform
{
public:
	CirclePlatform(FLOAT WorldX, FLOAT WorldY, FLOAT Width, FLOAT Height, FLOAT Period);
	~CirclePlatform();

	D3DXVECTOR2 GetPosition() override;
	D3DXVECTOR2 GetVelocity() override;
	float GetVelocityX() override;
	float GetVelocityY() override;
	BoundingBox GetBoundingBox() override;
	void Update(float dt) override;
	void Draw() override;
private:
	Animation *platform, *JetEngineHorizontal, *JetEngineVertical;
	float Ax, Ay, omega, t;
	D3DXVECTOR2 VirtualPoint, DrawPoint;
	float deltaX, deltaY;
	int FrameCounter;
};

