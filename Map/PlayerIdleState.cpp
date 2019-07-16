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
	//Debug::PrintOut(L"x = %f\n", player->GetPosition().x);

}

void PlayerIdleState::Draw()
{

}

void PlayerIdleState::Render()
{
}

void PlayerIdleState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	// Nếu ấn right-arrow thì chạy qua phải
	if (keyboard->KeyDown(RIGHT_KEY)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		return;
	}
	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->KeyDown(LEFT_KEY)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		return;
	}
	// Nếu ấn X thì nhảy
	if (keyboard->KeyDown(JUMP_KEY)) {
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	// Nếu vừa ấn cả up và down arrow thì giữ nghuyên idle
	if (keyboard->KeyDown(UP_KEY) && keyboard->KeyDown(DOWN_KEY)) {
		return;
	}

	// Nếu nhấn up-arrow thì gồng - shield up 
	if (keyboard->KeyDown(UP_KEY)) {
		player->ChangeState(new PlayerShieldUpState());
		return;
	} 
	
	// Nếu nhấn down-arrow thì duck
	if (keyboard->KeyDown(DOWN_KEY)) {
		player->ChangeState(new PlayerDuckingState());
		return;
	}
	if (keyboard->KeyDown(ATTACK_KEY)) {
		player->ChangeState(new PlayerThrowingState());
		return;
	}
}
