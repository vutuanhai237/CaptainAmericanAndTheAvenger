#include "PlayerDuckingState.h"
#include "Framework//Debug.h"
PlayerDuckingState::PlayerDuckingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::ducking);
	this->current_state = PlayerState::NameState::ducking;
	player->SetTimeBuffer(0);
}
PlayerDuckingState::~PlayerDuckingState()
{

}

void PlayerDuckingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->SetVelocity(0, 0);
	//Debug::PrintOut(L"x = %f\n", player->GetPosition().x);

}

void PlayerDuckingState::Draw()
{

}

void PlayerDuckingState::Render()
{
}

void PlayerDuckingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	this->IsDucking = true;
	// Ưu tiên trạng thái running
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
	// Chuyển sang đứng
	if (keyboard->KeyDown(UP_KEY)) {
		player->ChangeState(new PlayerIdleState());
		return;
	}
	// Tiếp tục giữ state
	if (keyboard->KeyDown(DOWN_KEY)) {
		return;
	}
	// Chuyển sang state chui xuyên đất
	if (keyboard->KeyDown(JUMP_KEY)) {
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	
	// Ngồi đấm
	if (keyboard->KeyDown(ATTACK_KEY)) {
		player->ChangeState(new PlayerDuckingPunchingState());

		return;
	}
	
	player->ChangeState(new PlayerIdleState());
	return;
}
