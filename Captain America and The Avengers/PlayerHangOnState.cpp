#include "PlayerHangOnState.h"
#include "Framework//Debug.h"
#include "Shield.h"
#include "ShieldOnAirState.h"
PlayerHangOnState::PlayerHangOnState()
{
	Player* player = Player::GetInstance();
	player->SetSize(24, 12);

	player->SetCurrentState(PlayerState::NameState::hang_on);
	Shield::GetInstance()->SetShieldState(new ShieldOnAirState());
	this->current_state = PlayerState::NameState::hang_on;
	this->IsJumpFromRope = false;
	this->time_jump_form_rope = 0.0f;
	player->SetTimeBuffer(0);
	player->SetVelocity(0, 0);

	player->time_air_jumping = 0;
	player->time_kicking = 0;
	player->time_air_rolling = 0;
	player->time_ducking_before_idle = 0;
	player->time_jumping_before_flowing = 0;

	player->IsJumpingDown = false;
	player->IsJumping = false;
	player->IsRolling = false;
	player->IsDonTho = false;
	player->IsLockCollision = false;
	player->IsShieldDown = false;
	player->OnTheWater = false;
	player->IsOnAir = false;

}
PlayerHangOnState::~PlayerHangOnState()
{

}

void PlayerHangOnState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
}

void PlayerHangOnState::Draw()
{
}

BoundingBox PlayerHangOnState::GetBoundingBox()
{
	Player *player = Player::GetInstance();
	SIZE size; size.cx = 24; size.cy = 28;
	D3DXVECTOR2 pos = player->GetPosition(); pos.y -= 7;
	return BoundingBox(pos, size, player->GetVelocityX(), player->GetVelocityY());
}

void PlayerHangOnState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (this->time_jump_form_rope > TIME_JUMP_FROM_ROPE) {
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	if (this->IsJumpFromRope) {
		this->time_jump_form_rope += dt;
		player->SetCurrentAnimation(player->GetAnimation(PlayerState::jump_from_rope));
		player->SetPositionY(player->GetPosition().y + 3);

		return;
	}
	if (keyboard->KeyPress(DOWN_KEY)) {
		player->ChangeState(new PlayerJumpingDownState());
		player->SetPositionY(player->GetPosition().y - 15);
		return;
	}
	if (keyboard->KeyDown(JUMP_KEY)) {
		this->IsJumpFromRope = true;
		return;
	}
	if (keyboard->KeyDown(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		return;
	}
	if (keyboard->KeyDown(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		return;
	}
		


	return;
}
