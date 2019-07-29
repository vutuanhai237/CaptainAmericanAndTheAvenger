#pragma once
#include "Entity.h"

#define ON_OFF_SWITCH_TIME_BETWEEN_ATTACK 0.3f

class OnOffSwitch :	public Entity
{
public:
	OnOffSwitch(int WorldX, int WorldY);
	int OnCollision(Entity *, float dt) override;
	void Update(float dt) override;
private:
	float InvincibleTimeCounter;
};

