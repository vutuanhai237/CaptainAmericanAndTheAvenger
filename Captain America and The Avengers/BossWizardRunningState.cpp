#include "BossWizardIdleState.h"
#include "BossWizardFlyingState.h"
#include "BossWizardRunningState.h"
#include "BossWizardFireState.h"
BossWizardRunningState::BossWizardRunningState()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::running);
	this->current_state = BossWizardState::NameState::running;
	boss->SetVelocity(BOSS_WIZARD_VELOCITY_X, 0);
	boss->SetSize(20, 45);
}


BossWizardRunningState::~BossWizardRunningState()
{
}

void BossWizardRunningState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);

	auto keyboard = DirectInput::GetInstance();
	Player* player = Player::GetInstance();

	if (keyboard->KeyPress(DIK_A)) {
		boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		return;

	}
	if (keyboard->KeyPress(DIK_D)) {
		boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		return;
	}
	boss->ChangeState(new BossWizardIdleState());
	return;
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
