#include "PlayerIdleState.h"
#include "Framework//Debug.h"
#include "Shield.h"
#include "ShieldNomalState.h"
#include "PlayerPunchingState.h"
PlayerIdleState::PlayerIdleState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::idle);
	this->current_state = PlayerState::NameState::idle;
	player->SetVelocity(0, 0);


	// Đảm bảo trạng thái nhảy chỉ được tiếp tục lần tới sau khi chạm đất
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
	Shield::GetInstance()->SetShieldState(new ShieldNomalState());
}
PlayerIdleState::~PlayerIdleState()
{

}

void PlayerIdleState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->SetVelocity(0, 0);

	//Debug::PrintOut(L"x = %f\n", player->GetPosition().x);

}

void PlayerIdleState::Draw()
{
}

void PlayerIdleState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (!player->IsCollisionWithWall(dt))
	{ 
		if (!player->IsCollisionWithGround(dt))
		{
			player->ChangeState(new PlayerJumpingDownState());
			return;
		}

	}
	
	// Nếu ấn X thì nhảy
	if (keyboard->KeyDown(JUMP_KEY)) {
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	if (keyboard->KeyDown(ATTACK_KEY)) {
		if (Shield::GetInstance()->GetShieldState()->GetFrameLock() >= 2) {
			player->ChangeState(new PlayerPunchingState());
			return;
		}
		else {
			
			player->ChangeState(new PlayerThrowingState());
			return;
		}
	
	}
	if (keyboard->KeyPress(RIGHT_KEY) && keyboard->KeyPress(LEFT_KEY)) {
		return;
	}
	// Nếu vừa ấn cả up và down arrow thì giữ nghuyên idle
	if (keyboard->KeyPress(UP_KEY) && keyboard->KeyPress(DOWN_KEY)) {
		return;
	}

	// Nếu nhấn up-arrow thì gồng - shield up 
	if (keyboard->KeyPress(UP_KEY)) {
		player->ChangeState(new PlayerShieldUpState());
		return;
	} 
	
	// Nếu nhấn down-arrow thì duck
	if (keyboard->KeyPress(DOWN_KEY)) {
		player->ChangeState(new PlayerDuckingState());
		return;
	}
	// Nếu ấn right-arrow thì chạy qua phải
	if (keyboard->KeyDown(RIGHT_KEY) || keyboard->KeyPress(RIGHT_KEY)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		return;
	}

	// Nếu ấn left-arrow thì chạy qua trái
	if (keyboard->KeyDown(LEFT_KEY) || keyboard->KeyPress(LEFT_KEY)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		return;
	}

}
