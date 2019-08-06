#pragma once
#include "BossWizardRoad.h"
#include "Equation.h"

class BossWizardFireRoad : public BossWizardRoad
{
public:
	int phase;
	int IsJumpingFirst;
	float time_fire;
	float time_running;
	float time_laugh;
	bool IsFiring;
	bool IsRunning;
	bool IsJumping;
	bool UpdateOneTime;
	Equation* e;
	virtual void Update(float dt);
	BossWizardFireRoad();
	~BossWizardFireRoad();
};

