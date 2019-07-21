#pragma once
#include "ShieldState.h"

#define SHIELD_NOMAL_KICKING_DELTA_X -8.5f
#define SHIELD_NOMAL_KICKING_DELTA_Y 0.0f

class ShieldKickState : public ShieldState
{
public:
	ShieldKickState();
	void Update(float dt) override;
	void Draw() override;
};