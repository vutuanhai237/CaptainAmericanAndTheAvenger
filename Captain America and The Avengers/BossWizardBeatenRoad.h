#pragma once
#include "BossWizardRoad.h"
class BossWizardBeatenRoad : public BossWizardRoad
{
public:
	int phase;
	bool UpdateOneTime;
	int delta_lui;
	virtual void Update(float dt);
	BossWizardBeatenRoad();
	~BossWizardBeatenRoad();
};

