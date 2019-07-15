#include "PlayerRunningState.h"
#include "PlayerIdleState.h"
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
	
	player->GetCurrentAnimation()->Update(dt);
	float new_x = player->GetPosition().x;
	
	int velocity_x = player->GetVelocity().x;

	player->SetPosition(new_x + dt*velocity_x, 100.0f);
	Debug::PrintOut(L"x = %f\n", player->GetPosition().x);
}

void PlayerRunningState::Draw()
{
}

void PlayerRunningState::Render()
{
}

void PlayerRunningState::HandleInput()
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (keyboard->GetKeyDown(DIK_LEFTARROW)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetVelocity(-20.0f, 0.0f);
		return;
	}
	if (keyboard->GetKeyDown(DIK_RIGHTARROW)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetVelocity(20.0f, 0.0f);
		return;
	}
	player->ChangeState(new PlayerIdleState());
	return;
}
