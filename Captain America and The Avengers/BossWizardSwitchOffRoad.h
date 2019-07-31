#pragma once
#include "BossWizardRoad.h"
#include "Equation.h"
class BossWizardSwitchOffRoad : public BossWizardRoad
{
public:
	float time_idle_before_jump;
	bool UpdateOneTime4;
	bool UpdateOneTime;
	bool UpdateOneTime2;
	bool UpdateOneTime3;


	Equation * e;
	int phase;
	bool FireOneTime;
	bool IsJumping;
	int IsJumpingFirst;
	virtual void Update(float dt);
	BossWizardSwitchOffRoad();
	~BossWizardSwitchOffRoad();
};

