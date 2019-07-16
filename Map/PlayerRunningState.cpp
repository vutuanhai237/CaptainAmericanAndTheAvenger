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
	// Đang ở trạng thái running, nếu ấn left thì vẫn giữ trạng thái
	if (keyboard->KeyDown(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetVelocityX(-VELOCITY_X);
		// vừa ấn left-arrow vừa nhấn x thì nhảy chéo
		if (keyboard->KeyDown(JUMP_KEY)) {
			player->ChangeState(new PlayerJumpingState());
			return;
		}
		/*
		// Nhấn left thêm lần nữa thì dashing
		if (keyboard->KeyDown(LEFT_KEY) && player->GetTimeBuffer() < 0.16f) {
			player->SetVelocityX(-VELOCITY_X * 3);
			player->ChangeState(new PlayerDashingState());
			return;
		}
		*/
		return;

	}

	if (keyboard->KeyDown(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetVelocityX(VELOCITY_X);
		// vừa ấn right-arrow vừa nhấn x thì nhảy chéo
		if (keyboard->KeyDown(JUMP_KEY)) {
			player->ChangeState(new PlayerJumpingState());
			return;
		}
		
		/*
		if (keyboard->KeyUp(DIK_RIGHTARROW) == true && keyboard->KeyPressed(DIK_RIGHTARROW) == true) {
			DataCollect* data_collect = DataCollect::GetInstance();
			data_collect->SetIsDashing(true);
			if (data_collect->GetIsDashing()) {
				Debug::PrintOut(L"IsDashing true");
			}
		}
		
		if (keyboard->KeyDown(DIK_RIGHTARROW)) {
			Debug::PrintOut(L"KeyDown down\n");
			keyboard->UpdateTimePressed(dt, DIK_RIGHTARROW);
		}
		Debug::PrintOut(L"%f",keyboard->GetTimePressed(DIK_RIGHTARROW));
		if (keyboard->KeyPressed(DIK_RIGHTARROW)) {
			Debug::PrintOut(L"KeyPressed\n");
			keyboard->GetTimePressed(DIK_RIGHTARROW);
		}
		if (keyboard->KeyReleased(DIK_NUMPAD6)) {
			Debug::PrintOut(L"KeyReleased down\n");
			keyboard->SetTimePressed(DIK_RIGHTARROW, 0);
		}
		
		// Nhấn right thêm lần nữa thì dashing
		if (keyboard->KeyDown(DIK_RIGHTARROW) && player->GetTimeBuffer() < 0.16f) {
			player->SetVelocityX(3 * VELOCITY_X);
			player->ChangeState(new PlayerDashingState());
			return;
		}
		*/
		return;
	}
	player->ChangeState(new PlayerIdleState());
	return;
}
