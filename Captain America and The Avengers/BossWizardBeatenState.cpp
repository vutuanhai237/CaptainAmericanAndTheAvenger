#include "BossWizardBeatenState.h"

BossWizardBeatenState::BossWizardBeatenState()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::beaten);
	this->current_state = BossWizardState::NameState::beaten;
	boss->SetVelocity(0, 0);
	boss->SetSize(20, 45);
}

BossWizardBeatenState::~BossWizardBeatenState()
{
}

void BossWizardBeatenState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	Player* player = Player::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);
	
}

void BossWizardBeatenState::Draw()
{
}

BoundingBox BossWizardBeatenState::GetBoundingBox()
{
	return BoundingBox();
}

void BossWizardBeatenState::HandleInput(float dt)
{
}
