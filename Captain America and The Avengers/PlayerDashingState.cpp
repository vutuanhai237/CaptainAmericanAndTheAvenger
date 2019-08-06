#include "PlayerDashingState.h"
#include "PlayerIdleState.h"
#include "Framework/SoundManager.h"
PlayerDashingState::PlayerDashingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::dashing);
	this->current_state = PlayerState::NameState::dashing;
	player->SetTimeBuffer(0);
	player->SetVelocityX(VELOCITY_X * 3);
	IsDucking = false;
	IsGong = false;
	SoundManager::GetInstance()->Play(SoundManager::SoundList::player_dash);
}

PlayerDashingState::~PlayerDashingState()
{
}

void PlayerDashingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
}

void PlayerDashingState::Draw()
{
}

BoundingBox PlayerDashingState::GetBoundingBox()
{
	Player *player = Player::GetInstance();
	SIZE size; size.cx = 24; size.cy = 28;
	D3DXVECTOR2 pos = player->GetPosition(); pos.y -= 7;
	return BoundingBox(pos, size, player->GetVelocityX(), player->GetVelocityY());
}

//Perfect, không được sửa nữa
void PlayerDashingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (!player->IsCollisionWithWall(dt))
	{
		if (!player->IsCollisionWithGround(dt))
		{
			player->SetVelocityX(VELOCITY_X);
			player->ChangeState(new PlayerJumpingDownState());
			return;
		}
	}
	if (keyboard->KeyDown(JUMP_KEY)) {
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	// Hiển thị sprite đầu trong time_duck_before dashing, sau đó xét đến sprite 2
	if (player->GetCurrentAnimation()->GetNumberCurrentFrame() == 1 && IsDucking == false)
	{
		player->GetCurrentAnimation()->Pause(TIME_DUCK_BEFORE_DASHING);
		IsDucking = true;
		goto CHECK;
	}
	// Giữ sprite 2 trong TIME_WAIT_DASHING, sau đó xét đến sprite 3
	if (player->GetCurrentAnimation()->GetNumberCurrentFrame() == 2 && IsGong == false)
	{
		player->GetCurrentAnimation()->Pause(TIME_WAIT_DASHING);
		IsGong = true;
		goto CHECK;
	}
	if (player->GetCurrentAnimation()->GetNumberCurrentFrame() == 3)
	{
		player->GetCurrentAnimation()->Pause(TIME_DASHING-(TIME_WAIT_DASHING+TIME_DUCK_BEFORE_DASHING));
	}
	// Dừng dashing khi time out hoặc thả nút left/right
	CHECK:
	if (player->GetCurrentAnimation()->GetAnimationTime() >= TIME_DASHING)
	{
		player->GetCurrentAnimation()->SetAnimationTime(0.0f);
		player->GetCurrentAnimation()->ResetAnimation();
		player->ChangeState(new PlayerIdleState());
		return;
	}
	else {
		if (player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight && keyboard->KeyUp(RIGHT_KEY))
		{
			player->GetCurrentAnimation()->SetAnimationTime(0.0f);
			player->GetCurrentAnimation()->ResetAnimation();
			player->ChangeState(new PlayerIdleState());
			return;
		}
		if (player->GetMoveDirection() == Entity::Entity_Direction::RightToLeft && keyboard->KeyUp(LEFT_KEY)) 
		{
			player->GetCurrentAnimation()->SetAnimationTime(0.0f);
			player->GetCurrentAnimation()->ResetAnimation();
			player->ChangeState(new PlayerIdleState());
			return;
		}
		
	}
}