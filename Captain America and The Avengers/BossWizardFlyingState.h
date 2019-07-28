#pragma once
#include "BossWizardState.h"
#include "BossWizard.h"
#include "Framework//DirectInput.h"
class BossWizardFlyingState : public BossWizardState
{
public:
	BossWizardFlyingState();
	~BossWizardFlyingState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

