#include "PlayerKickingState.h"
#include "PlayerIdleState.h"

#include "Framework//Debug.h"
PlayerKickingState::PlayerKickingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::kicking);
	this->current_state = PlayerState::NameState::kicking;
	player->SetVelocityY(VELOCITY_Y);
	this->time_kicking = TIME_KICKING;

}
PlayerKickingState::~PlayerKickingState()
{

}

void PlayerKickingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	if (this->time_kicking < 0) {
		if (player->GetJumpDirection() == Entity::Entity_Jump_Direction::BotToTop) {
			player->ChangeState(new PlayerJumpingState());
			return;
		}
		if (player->GetJumpDirection() == Entity::Entity_Jump_Direction::TopToBot) {
			player->ChangeState(new PlayerJumpingDownState());
			return;
		}
	}
	else {
		time_kicking -= dt;
	}
	Debug::PrintOut(L"y = %f\n", player->GetPosition().y);
}

void PlayerKickingState::Draw()
{

}

void PlayerKickingState::Render()
{
}

void PlayerKickingState::HandleInput(float dt)
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
