#include "BossWizardIdleState.h"
#include "BossWizardFlyingState.h"
#include "BossWizardRunningState.h"
#include "BossWizardFireState.h"
#include "BossWizardFlyingFireState.h"
BossWizardFlyingState::BossWizardFlyingState()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::flying);
	this->current_state = BossWizardState::NameState::flying;
	boss->SetVelocity(0, 50);
	boss->SetSize(20, 45);
}


BossWizardFlyingState::~BossWizardFlyingState()
{
}

void BossWizardFlyingState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);
	Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (boss->IsCollisionWithGround(dt)) {
		boss->ChangeState(new BossWizardIdleState());
		return;
	}
	if (keyboard->KeyPress(DIK_F)) {
		boss->ChangeState(new BossWizardFlyingFireState());
		return;
	}
	if (keyboard->KeyPress(DIK_W)) {
		boss->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
		boss->SetVelocity(0, BOSS_WIZARD_VELOCITY_Y);
		boss->GetCurrentAnimation()->SetFrame(1);
		return;
	}
	if (keyboard->KeyPress(DIK_A)) {
		boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		boss->SetPositionX(boss->GetPosition().x - 1);
		boss->SetVelocity(BOSS_WIZARD_VELOCITY_X, 0);
		return;

	}
	if (keyboard->KeyPress(DIK_S)) {
		boss->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
		boss->SetPositionY(boss->GetPosition().y - 1);
		boss->SetVelocity(0, BOSS_WIZARD_VELOCITY_Y);
		boss->GetCurrentAnimation()->SetFrame(2);
		return;

	}
	if (keyboard->KeyPress(DIK_D)) {
		boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		boss->SetPositionX(boss->GetPosition().x + 1);
		boss->SetVelocity(BOSS_WIZARD_VELOCITY_X, 0);
		return;


	}
	
}

void BossWizardFlyingState::Draw()
{
}

BoundingBox BossWizardFlyingState::GetBoundingBox()
{
	return BoundingBox();
}

void BossWizardFlyingState::HandleInput(float dt)
{
}
