#include "PlayerKickingState.h"
#include "PlayerIdleState.h"
#include "PlayerRollingState.h"
#include "Framework//Debug.h"
PlayerKickingState::PlayerKickingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::kicking);
	this->current_state = PlayerState::NameState::kicking;
	player->SetVelocityY(VELOCITY_Y/2);
}
PlayerKickingState::~PlayerKickingState()
{

}

void PlayerKickingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->time_kicking += dt;

	if (player->time_kicking >= TIME_KICKING) {
		if (player->GetPreviousState() == PlayerState::NameState::jumping)
		{

			player->ChangeState(new PlayerJumpingState());
			return;
		}
		if (player->GetPreviousState() == PlayerState::NameState::jumping_down)
		{
			player->ChangeState(new PlayerJumpingDownState());
			return;
		}
		if (player->GetPreviousState() == PlayerState::NameState::rolling)
		{
			player->ChangeState(new PlayerRollingState());
			return;
		}
	}
	
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
	if (player->IsCollisionWithGround(dt))
	{
		player->ChangeState(new PlayerIdleState());
		return;
	}
	// Đang ở trên không, nếu ấn left thì dịch qua trái
	if (keyboard->KeyPress(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - DELTA_JUMP);
		//return;
	}
	// Đang ở trên không, nếu ấn left thì dịch qua phải
	if (keyboard->KeyPress(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + DELTA_JUMP);
		//return;
	}
	
	// Code xong va chạm thì xóa hàm này với bỏ comment return chỗ left & right
	// SWEPT AABB sẽ giải quyết được bug chỗ này

}
