#pragma once
#include "BossWizardRoad.h"
#include "Entity.h"

class BossWizardUMaxRoad: public BossWizardRoad
{
public:
	int phase;
	int loop;
	float time_fire;
	float time_idle_before_jump;
	bool FireOneTime;
	bool UpdateOneTime;
	bool UpdateOneTime2;
	Entity::Entity_Direction direction_u_max;
	virtual void Update(float dt);
	void Release();
	BossWizardUMaxRoad();
	~BossWizardUMaxRoad();
};

