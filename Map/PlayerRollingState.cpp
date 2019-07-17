#include "PlayerRollingState.h"
#include "PlayerIdleState.h"

#include "Framework//Debug.h"
PlayerRollingState::PlayerRollingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::rolling);
	this->current_state = PlayerState::NameState::rolling;
	player->SetSize(0, 0);

	player->SetVelocityY(VELOCITY_Y);
	player->SetIsOnAir(true);
	player->SetTimeBuffer(0);
	player->SetIsRolling(true);
	player->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);

	this->time_air = TIME_ROLLING;
}
PlayerRollingState::~PlayerRollingState()
{

}

void PlayerRollingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);

	if (player->GetPosition().y >= DISTANCE_ROLLING) {
		player->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
	}
	if (player->GetPosition().y <= DISTANCE_JUMPING && player->GetIsRolling() == true) {
		player->ChangeState(new PlayerJumpingState());

	}
	Debug::PrintOut(L"y = %f\n", player->GetPosition().y);
}

void PlayerRollingState::Draw()
{

}

void PlayerRollingState::Render()
{
}

void PlayerRollingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	// Đang ở trên không, nếu ấn left thì dịch qua trái
	if (keyboard->KeyPress(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - DELTA_JUMP);
		//return;
	}
	// Đang ở trên không, nếu ấn left thì dịch qua phải
	if (keyboard->KeyDown(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + DELTA_JUMP);
		//return;
	}
	// Code xong va chạm thì xóa hàm này với bỏ comment return chỗ left & right
	// SWEPT AABB sẽ giải quyết được bug chỗ này

}
