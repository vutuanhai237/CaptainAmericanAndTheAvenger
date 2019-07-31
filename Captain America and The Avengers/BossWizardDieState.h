#pragma once
#include "BossWizardState.h"
#include "BossWizard.h"
#include "Framework//DirectInput.h"

class BossWizardDieState : public BossWizardState
{
public:
	float time_die;
	BossWizardDieState();
	~BossWizardDieState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

