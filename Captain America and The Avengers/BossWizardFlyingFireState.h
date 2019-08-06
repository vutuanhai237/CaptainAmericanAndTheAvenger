#pragma once
#include "BossWizardState.h"
#include "BossWizard.h"

class BossWizardFlyingFireState : public BossWizardState
{
public:
	float time_flying_fire;
	int count_bullet;
	bool IsFire;
	BossWizardFlyingFireState(bool IsFire);
	~BossWizardFlyingFireState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

