#pragma once
#include "ShieldState.h"

#define SHIELD_ON_AIR_DELTA_X 3.5f
#define SHIELD_ON_AIR_DELTA_Y 4.0f

class ShieldOnAirState : public ShieldState
{
public:
	ShieldOnAirState();
	void Update(float dt) override;
	void Draw() override;
};