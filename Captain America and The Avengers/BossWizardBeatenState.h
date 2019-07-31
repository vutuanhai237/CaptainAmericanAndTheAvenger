#pragma once
#include "BossWizardState.h"
#include "BossWizard.h"
#include "Framework//DirectInput.h"

class BossWizardBeatenState : public BossWizardState
{
public:
	BossWizardBeatenState();
	~BossWizardBeatenState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

