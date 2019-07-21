#pragma once
#include "ShieldState.h"

#define SHIELD_ON_AIR_DELTA_X -3.5f
#define SHIELD_ON_AIR_DELTA_Y 5.0f

#define SHIELD_ON_AIR_DUCKING_PUNCHING_DELTA_X 2.5f
#define SHIELD_ON_AIR_DUCKING_PUNCHING_DELTA_Y -9.0f
class ShieldOnAirState : public ShieldState
{
public:
	ShieldOnAirState();
	void Update(float dt) override;
	void Draw() override;
};