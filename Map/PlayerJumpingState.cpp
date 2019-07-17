#include "PlayerJumpingState.h"
#include "PlayerIdleState.h"
#include "PlayerRollingState.h"
#include "Framework//Debug.h"
PlayerJumpingState::PlayerJumpingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::jumping);
	player->SetVelocityY(VELOCITY_Y);
	player->SetSize(2 >> 3, 5 >> 3);

	player->SetIsOnAir(true);
	player->SetTimeBuffer(0);
	player->SetIsRolling(false);
	player->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
	this->current_state = PlayerState::NameState::jumping;
	this->time_air = TIME_AIR;
}
PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	
	if (this->time_air <= 0) {
		player->ChangeState(new PlayerJumpingDownState());
		return;
	} 
	else {
		this->time_air -= dt;
	}
	if (player->GetPosition().y >= player->GetPositionIdle().y + DISTANCE_JUMPING && player->GetIsRolling() == false) {
		player->ChangeState(new PlayerRollingState());
		return;
	}
	if (player->GetPosition().y <= player->GetPositionIdle().y) {
		player->ChangeState(new PlayerIdleState());
		
		return;
	}
	Debug::PrintOut(L"y = %f\n", player->GetPosition().y);
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
	// Tiếp tục ở trên không nếu nhấn giữ X
	if (keyboard->KeyPress(JUMP_KEY) && player->GetIsRolling() == false ) {
		this->time_air = TIME_AIR;
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
	if (keyboard->KeyDown(ATTACK_KEY)) {
		player->ChangeState(new PlayerKickingState());
		return;
	}
	
	// Code xong va chạm thì xóa hàm này với bỏ comment return chỗ left & right
	// SWEPT AABB sẽ giải quyết được bug chỗ này
	
	
}
