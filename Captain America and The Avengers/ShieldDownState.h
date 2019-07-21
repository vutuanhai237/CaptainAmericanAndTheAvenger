#pragma once
#include "ShieldState.h"

#define SHIELD_DOWN_DELTA_X 0.5f
#define SHIELD_DOWN_DELTA_Y -18.0f

class ShieldDownState : public ShieldState
{
public:
	ShieldDownState();
	void Update(float dt) override;
	void Draw() override;
};