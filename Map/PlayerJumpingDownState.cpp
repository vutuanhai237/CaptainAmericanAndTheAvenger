#include "PlayerIdleState.h"
#include "PlayerRollingState.h"
#include "Framework//Debug.h"
PlayerJumpingDownState::PlayerJumpingDownState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::jumping_down);
	player->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
	this->current_state = PlayerState::NameState::jumping_down;
}
PlayerJumpingDownState::~PlayerJumpingDownState()
{

}

void PlayerJumpingDownState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	
}

void PlayerJumpingDownState::Draw()
{

}

void PlayerJumpingDownState::Render()
{
}

void PlayerJumpingDownState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();

	auto res = player->IsCollisionWithGround(dt);
	if (res.side == CollisionSide::bottom) {
		player->SetPositionY(player->GetPosition().y + res.CollisionTime*dt*player->GetVelocityY());
		player->ChangeState(new PlayerIdleState());
		return;
	}

	// Đang ở trên không, nếu ấn left thì dịch qua trái
	if (keyboard->KeyPress(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - DELTA_JUMP);
		return;
	}
	// Đang ở trên không, nếu ấn left thì dịch qua phải
	if (keyboard->KeyPress(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + DELTA_JUMP);
		return;
	}
	if (keyboard->KeyDown(ATTACK_KEY)) {
		player->ChangeState(new PlayerKickingState());
		return;
	}
	if (player->GetPosition().y <= player->GetPositionIdle().y) {
		player->ChangeState(new PlayerIdleState());
		return;
	}
	// Code xong va chạm thì xóa hàm này với bỏ comment return chỗ left & right
	// SWEPT AABB sẽ giải quyết được bug chỗ này


}
