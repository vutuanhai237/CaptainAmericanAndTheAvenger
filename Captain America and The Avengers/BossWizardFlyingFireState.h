#pragma once
#include "BossWizardState.h"
#include "BossWizard.h"
#include "Framework//DirectInput.h"

class BossWizardFlyingFireState : public BossWizardState
{
public:
	float time_flying_fire;
	int count_bullet;
	BossWizardFlyingFireState();
	~BossWizardFlyingFireState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

