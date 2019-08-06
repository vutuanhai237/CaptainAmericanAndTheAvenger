#pragma once
#include "BossWizardRoad.h"
#include "Equation.h"

class BossWizardSwitchOffRoad : public BossWizardRoad
{
public:
	int phase;
	int IsJumpingFirst;
	float time_idle_before_jump;
	bool UpdateOneTime4;
	bool UpdateOneTime;
	bool UpdateOneTime2;
	bool UpdateOneTime3;
	bool FireOneTime;
	bool IsJumping;
	Equation * e;
	virtual void Update(float dt);
	BossWizardSwitchOffRoad();
	~BossWizardSwitchOffRoad();
};

