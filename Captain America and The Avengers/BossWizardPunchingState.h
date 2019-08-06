#pragma once
#include "BossWizardState.h"
#include "BossWizard.h"

class BossWizardPunchingState : public BossWizardState
{
public:
	float time_punching;
	BossWizardPunchingState();
	~BossWizardPunchingState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

