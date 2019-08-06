#pragma once
#include "BossWizardRoad.h"

class BossWizardIdleRoad : public BossWizardRoad
{
public:
	int phase;
	float time_idle;
	float time_running;
	bool IsRunning;
	bool IsChamDatLanDau;
	virtual void Update(float dt);
	BossWizardIdleRoad();
	~BossWizardIdleRoad();
};

