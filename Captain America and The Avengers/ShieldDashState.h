#pragma once
#include "ShieldState.h"

class ShieldDashState : public ShieldState
{
public:
	ShieldDashState();
	void Update(float dt) override;
	void Draw() override;
};