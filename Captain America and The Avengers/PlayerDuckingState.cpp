#include "PlayerDuckingState.h"
#include "Framework//Debug.h"
#include "Shield.h"
#include "ShieldNomalState.h"
PlayerDuckingState::PlayerDuckingState()
{
	Player* player = Player::GetInstance();
	player->SetSize(24, 12);

	player->SetCurrentState(PlayerState::NameState::ducking);
	Shield::GetInstance()->SetShieldState(new ShieldNomalState());
	this->current_state = PlayerState::NameState::ducking;
	player->SetTimeBuffer(0);
	player->SetVelocity(0, 0);

}
PlayerDuckingState::~PlayerDuckingState()
{

}

void PlayerDuckingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);

}

void PlayerDuckingState::Draw()
{
}

BoundingBox PlayerDuckingState::GetBoundingBox()
{
	Player *player = Player::GetInstance();
	SIZE size; size.cx = 24; size.cy = 28;
	D3DXVECTOR2 pos = player->GetPosition(); pos.y -= 7;
	return BoundingBox(pos, size, player->GetVelocityX(), player->GetVelocityY());
}

void PlayerDuckingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	this->IsDucking = true;
	player->time_ducking_before_idle += dt;
	if (player->IsCollisionWithWall(dt))
	{
		if (keyboard->KeyDown(JUMP_KEY)) {
			player->ChangeState(new PlayerJumpingState());
			return;
		}
	}
	if (player->GetPreviousState() == PlayerState::NameState::jumping_down) {
		if (player->time_ducking_before_idle >= TIME_DUCKING_BEFORE_IDLE) {
			player->ChangeState(new PlayerIdleState());
			return;
		}
		return;
	}
 	// Ngồi đấm
	if (keyboard->KeyDown(ATTACK_KEY) && keyboard->KeyPress(DOWN_KEY)) {
		player->ChangeState(new PlayerDuckingPunchingState());
		return;
	}
	
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
	if (keyboard->KeyPress(UP_KEY)) {
		player->ChangeState(new PlayerIdleState());
		return;
	}
	// Chuyển sang state chui xuyên đất hoặc nhảy lên nếu tường không lọt được
	if (keyboard->KeyDown(JUMP_KEY)) {
		player->ChangeState(new PlayerJumpingDownState());
		player->IsDonTho = true;
		return;
	}
	// Tiếp tục giữ state
	if (keyboard->KeyPress(DOWN_KEY)) {
		player->ChangeState(new PlayerDuckingState());
		return;
	}

	player->ChangeState(new PlayerIdleState());
	return;
}
