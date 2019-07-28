#include "BossWizardIdleState.h"
#include "BossWizardFlyingState.h"
#include "BossWizardRunningState.h"
#include "BossWizardFireState.h"
#include "BossWizardPunchingState.h"
#include "BossWizardPunchingFireState.h"
BossWizardIdleState::BossWizardIdleState()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::idle);
	this->current_state = BossWizardState::NameState::idle;
	boss->SetSize(20, 45);
	boss->SetVelocity(0, 0);
	boss->GetCurrentAnimation()->SetFrame(1);
}


BossWizardIdleState::~BossWizardIdleState()
{
}

void BossWizardIdleState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);

	auto keyboard = DirectInput::GetInstance();
	
	if (keyboard->KeyDown(DIK_W)) {
		boss->ChangeState(new BossWizardFlyingState());
		return;
	}
	if (keyboard->KeyDown(DIK_A)) {
		boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		boss->ChangeState(new BossWizardRunningState());
		return;

	}
	if (keyboard->KeyDown(DIK_D)) {
		boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		boss->ChangeState(new BossWizardRunningState());
		return;
	}
	if (keyboard->KeyDown(DIK_SPACE)) {
		boss->ChangeState(new BossWizardFireState());
		return;
	}
	if (keyboard->KeyDown(DIK_F)) {
		boss->ChangeState(new BossWizardPunchingState());
		return;
	}
	if (keyboard->KeyDown(DIK_V)) {
		boss->ChangeState(new BossWizardPunchingFireState());
		return;
	}
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
