#include "PlayerDuckingPunchingState.h"

#include "Framework//Debug.h"
PlayerDuckingPunchingState::PlayerDuckingPunchingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::ducking_punching);
	this->current_state = PlayerState::NameState::ducking_punching;
	player->SetBoudingBox(3 >> 3, 3 >> 3);
	player->SetTimeBuffer(0);
	player->SetVelocity(0, 0);

}
PlayerDuckingPunchingState::~PlayerDuckingPunchingState()
{

}

void PlayerDuckingPunchingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
}

void PlayerDuckingPunchingState::Draw()
{

}

void PlayerDuckingPunchingState::Render()
{
}

void PlayerDuckingPunchingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	// Nếu đấm liên tục thì vẫn giữ nguyên
	if (keyboard->KeyDown(ATTACK_KEY) && keyboard->KeyPress(DOWN_KEY)) {
		return;
	}
	
	if (keyboard->KeyUp(ATTACK_KEY) && keyboard->KeyPress(DOWN_KEY)) {
		player->ChangeState(new PlayerDuckingState());

		return;
	}
	// Chuyển về duck
	//player->ChangeState(new PlayerIdleState());
	if (keyboard->KeyUp(DOWN_KEY)) {
		player->ChangeState(new PlayerIdleState());

		return;
	}
}
