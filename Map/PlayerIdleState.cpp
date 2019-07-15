#include "PlayerIdleState.h"
#include "Framework//Debug.h"
PlayerIdleState::PlayerIdleState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::idle);
	this->current_state = PlayerState::NameState::idle;
}
PlayerIdleState::~PlayerIdleState()
{

}

void PlayerIdleState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->SetVelocity(0, 0);
	Debug::PrintOut(L"x = %f\n", player->GetPosition().x);

}

void PlayerIdleState::Draw()
{

}

void PlayerIdleState::Render()
{
}

void PlayerIdleState::HandleInput()
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();

	if (keyboard->KeyDown(DIK_RIGHTARROW)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		return;
	}
	
	if (keyboard->KeyDown(DIK_LEFTARROW)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		return;
	}

	if (keyboard->KeyDown(DIK_UPARROW)) {
		player->ChangeState(new PlayerJumpingState());
		return;
	}
}
