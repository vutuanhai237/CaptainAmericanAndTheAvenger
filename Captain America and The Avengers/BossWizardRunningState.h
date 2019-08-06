#pragma once
#include "BossWizardState.h"
#include "BossWizard.h"

class BossWizardRunningState : public BossWizardState
{
public:
	BossWizardRunningState();
	~BossWizardRunningState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

