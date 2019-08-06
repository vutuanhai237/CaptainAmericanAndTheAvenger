#include "BossWizardDieState.h"

BossWizardDieState::BossWizardDieState()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::die);
	this->current_state = BossWizardState::NameState::die;
	boss->SetVelocity(0, 0);
	boss->SetSize(20, 45);
}

BossWizardDieState::~BossWizardDieState()
{
}

void BossWizardDieState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	Player* player = Player::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);
	boss->time_die += dt;
	if (boss->time_die >= 1.6)
	{
		boss->GetCurrentAnimation()->Stop();
		boss->GetCurrentAnimation()->SetFrame(2);
	}
	if (boss->time_die >= 2.6) 
	{
		SceneManager::GetInstance()->GetCurrentScene()->IsExitAble = true;
	}
}

void BossWizardDieState::Draw()
{
}

BoundingBox BossWizardDieState::GetBoundingBox()
{
	return BoundingBox();
}

void BossWizardDieState::HandleInput(float dt)
{
}
