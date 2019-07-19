#include "PlayerDivingState.h"
#include "Framework//Debug.h"
PlayerDivingState::PlayerDivingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::ducking);

	this->current_state = PlayerState::NameState::ducking;
	player->SetTimeBuffer(0);
	player->SetVelocity(0, 0);

}
PlayerDivingState::~PlayerDivingState()
{

}

void PlayerDivingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);

}

void PlayerDivingState::Draw()
{

}

void PlayerDivingState::Render()
{
}

void PlayerDivingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	this->IsDucking = true;
	player->time_ducking_before_idle += dt;
	if (player->GetPreviousState() == PlayerState::NameState::jumping_down) {
		if (player->time_ducking_before_idle >= TIME_DUCKING_BEFORE_IDLE) {
			player->ChangeState(new PlayerIdleState());
			return;
		}
		return;
	}
	// Ngồi đấm
	if (keyboard->KeyDown(ATTACK_KEY) && keyboard->KeyPress(DOWN_KEY)) {
		player->ChangeState(new PlayerDuckingPunchingState());
		return;
	}

	// Ưu tiên trạng thái running
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
	// Chuyển sang đứng
	if (keyboard->KeyPress(UP_KEY)) {
		player->ChangeState(new PlayerIdleState());
		return;
	}
	// Chuyển sang state chui xuyên đất hoặc nhảy lên nếu tường không lọt được
	if (keyboard->KeyDown(JUMP_KEY)) {
		player->ChangeState(new PlayerJumpingDownState());
		return;
	}
	// Tiếp tục giữ state
	if (keyboard->KeyPress(DOWN_KEY)) {
		player->ChangeState(new PlayerDuckingState());
		return;
	}

	player->ChangeState(new PlayerIdleState());
	return;
}
