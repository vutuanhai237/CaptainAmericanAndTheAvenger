#include "PlayerJumpingState.h"
#include "PlayerIdleState.h"
#include "PlayerRollingState.h"
#include "Framework//Debug.h"
PlayerJumpingState::PlayerJumpingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::jumping);
	if (player->IsJumping == false) {
		player->SetVelocityY(JUMPING_VELOCITY_BEGIN);
		player->IsJumping = true;
	}
	player->SetVelocityX(0);
	player->SetIsOnAir(true);
	player->SetTimeBuffer(0);
	player->SetIsRolling(false);
	player->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
	this->current_state = PlayerState::NameState::jumping;
	// Khi từ đá chuyển về nhảy thì mới có quyền đá tiếp
	player->time_kicking = 0;
}
PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	if (player->GetVelocityY() >= VELOCITY_Y) {
		player->SetVelocityY(abs(player->GetVelocityY()) - JUMPING_ACCELERATION);
	}
}

void PlayerJumpingState::Draw()
{

}

void PlayerJumpingState::Render()
{
}

void PlayerJumpingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();

	if (keyboard->KeyDown(ATTACK_KEY)) {
		player->ChangeState(new PlayerKickingState());
		return;
	}
	// Tiếp tục ở trên không nếu nhấn giữ X
	if (keyboard->KeyPress(JUMP_KEY))
	{
		player->time_air_jumping += dt;
		if (player->time_air_jumping >= TIME_AIR)
		{
			player->ChangeState(new PlayerRollingState());
			return;
		}
	}
	else
	{
		player->time_air_jumping += dt;
		player->SetVelocityY(player->GetVelocityY() - JUMPING_ACCELERATION);
		if (player->time_air_jumping >= TIME_JUMPING)
		{
			player->ChangeState(new PlayerJumpingDownState());
			return;
		}
	}
	if (!keyboard->KeyPress(RIGHT_KEY) && !keyboard->KeyPress(LEFT_KEY)) {
		player->SetVelocityX(0);
		return;
	}
	
	// Đang ở trên không, nếu ấn left thì dịch qua trái
	if (keyboard->KeyPress(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - DELTA_JUMP);
	}
	// Đang ở trên không, nếu ấn left thì dịch qua phải
	if (keyboard->KeyPress(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + DELTA_JUMP);
	}
	

	
	// Code xong va chạm thì xóa hàm này với bỏ comment return chỗ left & right
	// SWEPT AABB sẽ giải quyết được bug chỗ này
	
	
}
