#include "PlayerJumpingState.h"
#include "PlayerIdleState.h"

#include "Framework//Debug.h"
PlayerJumpingState::PlayerJumpingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::jumping);
	this->current_state = PlayerState::NameState::jumping;
	player->SetVelocityY(20.0f);
	player->SetIsOnAir(true);
}
PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
	Player* player = Player::GetInstance();

	player->GetCurrentAnimation()->Update(dt);
	float new_y = player->GetPosition().y;
	float velocity_y = player->GetVelocity().y;
	if (player->GetPosition().y == 120.0f) {
		player->SetVelocityY(abs(velocity_y - 5.0f));
	}
	player->SetPosition(50.0f, new_y + dt * velocity_y);
	Debug::PrintOut(L"y = %f\n", player->GetPosition().y);
}

void PlayerJumpingState::Draw()
{

}

void PlayerJumpingState::Render()
{
}

void PlayerJumpingState::HandleInput()
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	/*
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
	*/
	if (player->GetPosition().y == 100.0f) {
		player->ChangeState(new PlayerIdleState());
		return;
	}
	
}
