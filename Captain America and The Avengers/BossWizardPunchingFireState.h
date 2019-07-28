#pragma once
#include "BossWizardState.h"
#include "BossWizard.h"
#include "Framework//DirectInput.h"

class BossWizardPunchingFireState : public BossWizardState
{
public:
	float time_punching_fire;
	int count_bullet;
	BossWizardPunchingFireState();
	~BossWizardPunchingFireState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

