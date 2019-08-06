#include "PlayerRunningState.h"
#include "PlayerIdleState.h"
#include "PlayerDashingState.h"
#include "Shield.h"
#include "ShieldNomalState.h"
PlayerRunningState::PlayerRunningState()
{
	Player* player = Player::GetInstance();
	player->SetSize(20, 45);

	player->SetCurrentState(PlayerState::NameState::running);
	this->current_state = PlayerState::NameState::running;
	player->SetVelocityX(VELOCITY_X);
	Shield::GetInstance()->SetShieldState(new ShieldNomalState());
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

PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::Update(float dt)
{
	
	Player* player = Player::GetInstance();
	player->AddTimeBuffer(dt);
	player->GetCurrentAnimation()->Update(dt);
	
}

void PlayerRunningState::Draw()
{
}

BoundingBox PlayerRunningState::GetBoundingBox()
{
	Player * player = Player::GetInstance();
	return BoundingBox(
		player->GetPosition(),
		player->GetSize(),
		player->GetVelocityX(),
		player->GetVelocityY()
	);

}

void PlayerRunningState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (!player->IsCollisionWithWall(dt))
	{
		if (!player->IsCollisionWithGround(dt))
		{
			if (!player->IsCollisionWithSpike(dt))
			{
				if (!player->IsCollisionWithPlatform(dt))
				{
					player->ChangeState(new PlayerJumpingDownState());
					player->CarrierObject = NULL;
					return;
				}
			}	
		}
	}
	if (keyboard->KeyPress(RIGHT_KEY) && keyboard->KeyPress(LEFT_KEY)) {
		player->ChangeState(new PlayerIdleState());
		return;
	}
	// Set trạng thái lướt
	if (keyboard->KeyPress(RIGHT_KEY) && keyboard->GetLastPressKey() == RIGHT_KEY) {
		keyboard->ReleaseLastPressKey();
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->ChangeState(new PlayerDashingState());
		return;
	}
	// Lỗi keyboard nên set tạm ở đây bằng previous d
	if (keyboard->KeyPress(LEFT_KEY) && keyboard->GetLastPressKey() == LEFT_KEY) {
		keyboard->ReleaseLastPressKey();
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->ChangeState(new PlayerDashingState());
		return;
	}
	// Đang ở trạng thái running, nếu ấn left thì vẫn giữ trạng thái
	if (keyboard->KeyPress(LEFT_KEY) && keyboard->KeyDown(JUMP_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->previous_direction = Entity::Entity_Direction::RightToLeft;
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	if (keyboard->KeyPress(LEFT_KEY) && keyboard->KeyDown(ATTACK_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->previous_direction = Entity::Entity_Direction::RightToLeft;
		player->ChangeState(new PlayerThrowingState());
		return;
	}
		
	if (keyboard->KeyPress(RIGHT_KEY) && keyboard->KeyDown(JUMP_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->previous_direction = Entity::Entity_Direction::LeftToRight;
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	if (keyboard->KeyPress(RIGHT_KEY) && keyboard->KeyDown(ATTACK_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->previous_direction = Entity::Entity_Direction::LeftToRight;
		player->ChangeState(new PlayerThrowingState());
		return;
		
	}
	if (keyboard->KeyPress(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->previous_direction = Entity::Entity_Direction::RightToLeft;
		return;
	}
	if (keyboard->KeyPress(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->previous_direction = Entity::Entity_Direction::LeftToRight;
		return;
	}
	// Nếu không ấn gì thì đứng
	player->ChangeState(new PlayerIdleState());
	return;
}
