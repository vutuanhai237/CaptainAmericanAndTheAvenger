#include "PlayerShieldUpState.h"
#include "Framework//Debug.h"
PlayerShieldUpState::PlayerShieldUpState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::shield_up);
	this->current_state = PlayerState::NameState::shield_up;
	player->SetTimeBuffer(0);
}
PlayerShieldUpState::~PlayerShieldUpState()
{

}

void PlayerShieldUpState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->SetVelocity(0, 0);
	//Debug::PrintOut(L"x = %f\n", player->GetPosition().x);

}

void PlayerShieldUpState::Draw()
{

}

void PlayerShieldUpState::Render()
{
}

void PlayerShieldUpState::HandleInput(float dt)
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
	// Nếu vẫn up và down cùng lúc thì về idle

	if (keyboard->KeyPress(UP_KEY) && keyboard->KeyPress(DOWN_KEY)) {
		player->ChangeState(new PlayerIdleState());

		return;
	}
	// Nếu vẫn nhấn thì giữ nguyên trạng thái
	if (keyboard->KeyPress(UP_KEY)) {
		return;
	}
	if (keyboard->KeyPress(DOWN_KEY)) {
		player->ChangeState(new PlayerIdleState());
		return;
	}
	if (keyboard->KeyDown(ATTACK_KEY)) {
		player->ChangeState(new PlayerThrowingState());
		return;
	}
	if (keyboard->KeyDown(JUMP_KEY)) {
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	//player->ChangeState(new PlayerIdleState());
	return;
}
