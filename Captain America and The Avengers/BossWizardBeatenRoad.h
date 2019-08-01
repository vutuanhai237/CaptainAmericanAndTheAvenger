#pragma once
#include "BossWizardRoad.h"
#include "Equation.h"
class BossWizardBeatenRoad : public BossWizardRoad
{
public:
	int phase;
	float time_beaten;
	bool UpdateOneTime;
	int count_jump;
	int jump_high;
	float previous_y;
	Equation* e;
	D3DXVECTOR2 position_goto;
	virtual void Update(float dt);
	BossWizardBeatenRoad();
	~BossWizardBeatenRoad();
};

