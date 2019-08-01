#pragma once
#include "BossWizardRoad.h"

class BossWizardIdleRoad : public BossWizardRoad
{
public:
	int phase;
	float time_idle;
	bool IsRunning;
	float time_running;

	bool IsChamDatLanDau;
	virtual void Update(float dt);
	BossWizardIdleRoad();
	~BossWizardIdleRoad();
};

