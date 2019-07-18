#include "PlayerRunningState.h"
#include "PlayerIdleState.h"
#include "PlayerDashingState.h"
#include "Framework//Debug.h"
PlayerRunningState::PlayerRunningState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::running);
	this->current_state = PlayerState::NameState::running;
	player->SetVelocityX(VELOCITY_X);

	
}

PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::Update(float dt)
{
	
	Player* player = Player::GetInstance();
	player->AddTimeBuffer(dt);
	player->GetCurrentAnimation()->Update(dt);
	
}

void PlayerRunningState::Draw()
{
}

void PlayerRunningState::Render()
{
}

void PlayerRunningState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (!player->IsCollisionWithGround(dt)) {
		player->ChangeState(new PlayerJumpingDownState());

		return;
	}
	if (keyboard->KeyPress(RIGHT_KEY) && keyboard->KeyPress(LEFT_KEY)) {
		player->ChangeState(new PlayerIdleState());
		return;
	}
	// Set trạng thái lướt
	if (keyboard->KeyPress(RIGHT_KEY) && keyboard->GetLastPressKey() == RIGHT_KEY) {
		keyboard->ReleaseLastPressKey();
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->ChangeState(new PlayerDashingState());
		return;
	}
	// Lỗi keyboard nên set tạm ở đây bằng previous d
	if (keyboard->KeyPress(LEFT_KEY) && keyboard->GetLastPressKey() == LEFT_KEY) {
		keyboard->ReleaseLastPressKey();
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->ChangeState(new PlayerDashingState());
		return;
	}
	// Đang ở trạng thái running, nếu ấn left thì vẫn giữ trạng thái
	if (keyboard->KeyPress(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->previous_direction = Entity::Entity_Direction::RightToLeft;
		// vừa ấn left-arrow vừa nhấn x thì nhảy chéo
		if (keyboard->KeyDown(JUMP_KEY)) {
			player->ChangeState(new PlayerJumpingState());
			return;
		}	
		if (keyboard->KeyDown(ATTACK_KEY)) {
			player->ChangeState(new PlayerThrowingState());
			return;
		}
		return;

	}
	if (keyboard->KeyPress(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->previous_direction = Entity::Entity_Direction::LeftToRight;

		// vừa ấn right-arrow vừa nhấn x thì nhảy chéo
		if (keyboard->KeyDown(JUMP_KEY)) {
			player->ChangeState(new PlayerJumpingState());
			return;
		}
		if (keyboard->KeyDown(ATTACK_KEY)) {
			player->ChangeState(new PlayerThrowingState());
			return;
		}	
		return;
	}

	// Nếu không ấn gì thì đứng
	player->ChangeState(new PlayerIdleState());
	return;
}
