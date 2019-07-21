#pragma once
#include "ShieldState.h"

#define SHIELD_UP_DELTA_X 3.0f
#define SHIELD_UP_DELTA_Y 17.5f

class ShieldUpState : public ShieldState
{
public:
	ShieldUpState();
	void Update(float dt) override;
	void Draw() override;
};