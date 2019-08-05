#pragma once
#include "Entity.h"
#include "Framework/Animation.h"

#define ELECTRIC_SHOCKWAVE_BARRIER_TIME_WAIT 2.0f
#define ELECTRIC_SHOCKWAVE_BARRIER_TIME_CROSS 1.5f

class ElectricShockwaveBarrier : public Entity
{
public:
	ElectricShockwaveBarrier(int WorldX, int WorldY);
	~ElectricShockwaveBarrier();

	int OnCollision(Entity *, float dt) override;
	BoundingBox GetBoundingBox() override;
	void Update(float dt) override;
	void Draw() override;

	static int ID;
private:
	Animation *animation;
	bool IsHaveElectric;
	float Timer;
};

