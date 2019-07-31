#pragma once
#include "Platform.h"
#include "Framework/Animation.h"

class MovingPlatform : public Platform
{
public:
	MovingPlatform(FLOAT WorldX, FLOAT WorldY, int Distance);
	~MovingPlatform();

	BoundingBox GetBoundingBox() override;
	int OnCollision(Entity *, float dt) override;
	void Update(float dt) override;
	void Draw() override;
private:
	Animation *platform, *JetEngine;
	int FarLeft, FarRight;
	int Direction;
};

