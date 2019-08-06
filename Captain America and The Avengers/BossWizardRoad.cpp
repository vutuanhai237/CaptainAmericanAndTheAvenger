#include "BossWizardRoad.h"
#include "BossWizardIdleState.h"

BossWizardRoad::RoadType BossWizardRoad::GetCurrentRoad()
{
	return this->current_road;
}

void BossWizardRoad::SetCurrentRoad(RoadType road)
{
	this->current_road = road;
}

BossWizardRoad::BossWizardRoad()
{	
}

BossWizardRoad::~BossWizardRoad()
{
}