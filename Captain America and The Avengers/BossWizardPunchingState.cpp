#include "BossWizardIdleState.h"
#include "BossWizardPunchingState.h"
#include "BossWizardRunningState.h"
#include "BossWizardFireState.h"
BossWizardPunchingState::BossWizardPunchingState()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::punching);
	this->current_state = BossWizardState::NameState::punching;
	boss->SetSize(20, 45);
	this->time_punching = 0.0f;
}


BossWizardPunchingState::~BossWizardPunchingState()
{
}

void BossWizardPunchingState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);
	this->time_punching += dt;
	if (this->time_punching >= BOSS_WIZARD_TIME_PUNCHING) {
		boss->ChangeState(new BossWizardIdleState());
		return;
	}
	else {
		return;
	}

}

void BossWizardPunchingState::Draw()
{
}

BoundingBox BossWizardPunchingState::GetBoundingBox()
{
	return BoundingBox();
}

void BossWizardPunchingState::HandleInput(float dt)
{
}
