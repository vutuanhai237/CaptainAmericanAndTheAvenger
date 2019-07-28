#pragma once
#include "BossWizardState.h"
#include "BossWizard.h"
#include "Framework//DirectInput.h"

class BossWizardFireState : public BossWizardState
{
public:
	float time_fire;
	float time_firing;
	float time_wait_before_fire_four_bullet;
	int count_bullet;
	BossWizardFireState();
	~BossWizardFireState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

