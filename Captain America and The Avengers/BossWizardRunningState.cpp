#include "BossWizardIdleState.h"
#include "BossWizardFlyingState.h"
#include "BossWizardRunningState.h"
#include "BossWizardFireState.h"
BossWizardRunningState::BossWizardRunningState()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::running);
	this->current_state = BossWizardState::NameState::running;
	boss->SetSize(20, 45);
}


BossWizardRunningState::~BossWizardRunningState()
{
}

void BossWizardRunningState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);

}

void BossWizardRunningState::Draw()
{
}

BoundingBox BossWizardRunningState::GetBoundingBox()
{
	return BoundingBox();
}

void BossWizardRunningState::HandleInput(float dt)
{
}
