#pragma once
#include "BossWizardRoad.h"
#include "Entity.h"
class BossWizardUMaxRoad: public BossWizardRoad
{
public:

	virtual void Update(float dt);
	Entity::Entity_Direction direction_u_max;
	float time_idle_before_jump;

	bool UpdateOneTime;
	bool UpdateOneTime2;

	int phase;	
	bool FireOneTime;
	int loop;
	//bool UpdateFireOn
	float time_fire;
	void Release();
	BossWizardUMaxRoad();
	~BossWizardUMaxRoad();
};

