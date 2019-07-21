#include "PlayerThrowingState.h"
#include "Framework//Debug.h"
#include "Shield.h"
#include "ShieldAttackState.h"
PlayerThrowingState::PlayerThrowingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::throwing);
	player->SetTimeBuffer(0);
	this->current_state = PlayerState::NameState::throwing;

	Shield::GetInstance()->SetShieldState(new ShieldAttackState());
}
PlayerThrowingState::~PlayerThrowingState()
{

}

void PlayerThrowingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->SetVelocity(0, 0);
}

void PlayerThrowingState::Draw()
{

}

void PlayerThrowingState::Render()
{
}

void PlayerThrowingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (player->GetCurrentAnimation()->GetNumberCurrentFrame() == 2)
	{
		player->GetCurrentAnimation()->Pause(TIME_WAIT_THROWING);
	}

	// Dừng throwing khi time out, chuyển về idle
	if (player->GetCurrentAnimation()->GetAnimationTime() >= TIME_THROWING)
	{
		player->GetCurrentAnimation()->SetAnimationTime(0.0f);
		player->GetCurrentAnimation()->SetFrame(1);
		player->ChangeState(new PlayerIdleState());
		return;
	}
	else {
		return;
	}
	// Ưu tiên các trạng thái khái
	if (keyboard->KeyDown(RIGHT_KEY)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		return;
	}

	if (keyboard->KeyDown(LEFT_KEY)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		return;
	}

	if (keyboard->KeyPress(JUMP_KEY)) {
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	
	if (keyboard->KeyDown(UP_KEY)) {
		player->ChangeState(new PlayerShieldUpState());
		return;
	}
	
	if (keyboard->KeyDown(DOWN_KEY)) {
		player->ChangeState(new PlayerDuckingState());
		return;
	}
	player->ChangeState(new PlayerIdleState());
	return;
}
