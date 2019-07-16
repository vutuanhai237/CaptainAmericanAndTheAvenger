#include "PlayerRunningState.h"
#include "PlayerIdleState.h"
#include "PlayerDashingState.h"
#include "Framework//Debug.h"
PlayerRunningState::PlayerRunningState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::running);
	this->current_state = PlayerState::NameState::running;

	
}

PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::Update(float dt)
{
	
	Player* player = Player::GetInstance();
	player->AddTimeBuffer(dt);

	player->GetCurrentAnimation()->Update(dt);
	float new_x = player->GetPosition().x;
	
	int velocity_x = player->GetVelocity().x;

	player->SetPosition(new_x + dt*velocity_x, 50.0f);
	//Debug::PrintOut(L"x = %f\n", player->GetPosition().x);
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
	// Set trạng thái lướt
	if (keyboard->KeyPress(RIGHT_KEY) && keyboard->GetLastPressKey() == RIGHT_KEY) {
		keyboard->ReleaseLastPressKey();
		player->SetVelocityX(VELOCITY_X * 3);
		player->ChangeState(new PlayerDashingState());
		return;
	}
	if (keyboard->KeyPress(LEFT_KEY) && keyboard->GetLastPressKey() == LEFT_KEY) {
		keyboard->ReleaseLastPressKey();

		player->SetVelocityX(-VELOCITY_X * 3);
		player->ChangeState(new PlayerDashingState());
		return;
	}
	// Đang ở trạng thái running, nếu ấn left thì vẫn giữ trạng thái
	if (keyboard->KeyPress(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetVelocityX(-VELOCITY_X);
		// vừa ấn left-arrow vừa nhấn x thì nhảy chéo
		if (keyboard->KeyDown(JUMP_KEY)) {
			player->ChangeState(new PlayerJumpingState());
			return;
		}	
		return;

	}
	if (keyboard->KeyPress(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetVelocityX(VELOCITY_X);
		// vừa ấn right-arrow vừa nhấn x thì nhảy chéo
		if (keyboard->KeyDown(JUMP_KEY)) {
			player->ChangeState(new PlayerJumpingState());
			return;
		}
		
	
		return;
	}
	player->ChangeState(new PlayerIdleState());
	return;
}
