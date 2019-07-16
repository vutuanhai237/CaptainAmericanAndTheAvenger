#include "PlayerDuckingPunchingState.h"

#include "Framework//Debug.h"
PlayerDuckingPunchingState::PlayerDuckingPunchingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::ducking_punching);
	this->current_state = PlayerState::NameState::ducking_punching;
	player->SetTimeBuffer(0);
}
PlayerDuckingPunchingState::~PlayerDuckingPunchingState()
{

}

void PlayerDuckingPunchingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->SetVelocity(0, 0);
	//Debug::PrintOut(L"x = %f\n", player->GetPosition().x);

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
	if (keyboard->KeyDown(ATTACK_KEY)) {
		return;
	}
	// Chuyển về duck
	player->ChangeState(new PlayerDuckingState());
	return;
}
