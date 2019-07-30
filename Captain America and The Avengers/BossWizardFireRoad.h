#pragma once
#include "BossWizardRoad.h"
#include "Equation.h"
class BossWizardFireRoad : public BossWizardRoad
{
public:
	int phase;
	float time_fire;
	bool IsFiring;
	bool IsRunning;
	bool IsJumping;
	bool UpdateOneTime;
	float time_running;
	int IsJumpingFirst;
	int previous_player_hp;
	Equation* e;
	virtual void Update(float dt);
	BossWizardFireRoad();
	~BossWizardFireRoad();
};
