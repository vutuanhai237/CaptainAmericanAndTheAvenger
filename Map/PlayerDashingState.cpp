#include "PlayerDashingState.h"
#include "PlayerIdleState.h"
#include "Framework//Debug.h"
PlayerDashingState::PlayerDashingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::dashing);
	this->current_state = PlayerState::NameState::dashing;
	player->SetTimeBuffer(0);


}

PlayerDashingState::~PlayerDashingState()
{
}

void PlayerDashingState::Update(float dt)
{

	Player* player = Player::GetInstance();

	player->GetCurrentAnimation()->Update(dt);
	float new_x = player->GetPosition().x;
	//player->SetVelocityX(VELOCITY_X*3);
	
	int velocity_x = player->GetVelocity().x;

	player->SetPosition(new_x + dt * velocity_x, 50.0f);
	//Debug::PrintOut(L"x = %f\n", player->GetPosition().x);

}

void PlayerDashingState::Draw()
{
}

void PlayerDashingState::Render()
{
}

void PlayerDashingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (player->GetCurrentAnimation()->GetNumberCurrentFrame() == 2)
	{
		player->GetCurrentAnimation()->Pause(0.016f * 18.0f);
	}
	if (player->GetCurrentAnimation()->GetAnimationTime() >= 0.016f * 20.0f)
	{
		player->GetCurrentAnimation()->ResetAnimation();
		player->ChangeState(new PlayerIdleState());
		return;
	}
	player->GetCurrentAnimation()->ResetAnimation();
	player->ChangeState(new PlayerIdleState());

}
