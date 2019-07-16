#include "PlayerThrowingState.h"
#include "Framework//Debug.h"
PlayerThrowingState::PlayerThrowingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::throwing);
	this->current_state = PlayerState::NameState::throwing;
	player->SetTimeBuffer(0);
}
PlayerThrowingState::~PlayerThrowingState()
{

}

void PlayerThrowingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->SetVelocity(0, 0);
	//Debug::PrintOut(L"x = %f\n", player->GetPosition().x);

}

void PlayerThrowingState::Draw()
{

}

void PlayerThrowingState::Render()
{
}

void PlayerThrowingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	// Ưu tiên các trạng thái khái
	if (keyboard->KeyDown(RIGHT_KEY)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		return;
	}

	if (keyboard->KeyDown(LEFT_KEY)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		return;
	}

	if (keyboard->KeyDown(ATTACK_KEY)) {
		return;
	}
	if (keyboard->KeyDown(JUMP_KEY)) {
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	
	if (keyboard->KeyDown(UP_KEY)) {
		player->ChangeState(new PlayerShieldUpState());
		return;
	}
	
	if (keyboard->KeyDown(DOWN_KEY)) {
		player->ChangeState(new PlayerDuckingState());
		return;
	}
	player->ChangeState(new PlayerIdleState());
	return;
}
