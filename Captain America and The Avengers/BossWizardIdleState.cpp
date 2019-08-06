#include "BossWizardIdleState.h"

BossWizardIdleState::BossWizardIdleState()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::idle);
	this->current_state = BossWizardState::NameState::idle;
	boss->SetSize(20, 45);
	boss->GetCurrentAnimation()->SetFrame(1);
}

BossWizardIdleState::~BossWizardIdleState()
{
}

void BossWizardIdleState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);
}

void BossWizardIdleState::Draw()
{
}

BoundingBox BossWizardIdleState::GetBoundingBox()
{
	return BoundingBox();
}

void BossWizardIdleState::HandleInput(float dt)
{
}
