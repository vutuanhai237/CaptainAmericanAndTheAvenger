#include "PlayerDuckingPunchingState.h"
#include "Shield.h"
#include "ShieldOnAirState.h"
#include "Framework//Debug.h"
PlayerDuckingPunchingState::PlayerDuckingPunchingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::ducking_punching);
	this->current_state = PlayerState::NameState::ducking_punching;
	player->SetTimeBuffer(0);
	player->SetVelocity(0, 0);
	this->time_punch = 0;

	Shield::GetInstance()->SetShieldState(new ShieldOnAirState());

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
	time_punch += dt;
	if (player->GetCurrentAnimation()->GetNumberCurrentFrame() == 1)
	{
		player->GetCurrentAnimation()->Pause(TIME_WAITING_DUCKING_PUNCHING);
	}
	if (this->time_punch >= TIME_DUCKING_PUNCHING)
	{
		
		player->GetCurrentAnimation()->SetAnimationTime(0.0f);
		player->GetCurrentAnimation()->ResetAnimation();
		player->ChangeState(new PlayerDuckingState());
		return;
	}
	
	// Chuyển về duck
	//player->ChangeState(new PlayerIdleState());
	
	if (keyboard->KeyUp(ATTACK_KEY)) {
		return;
	}
}
