#include "PlayerDashingState.h"
#include "PlayerIdleState.h"
#include "Framework//Debug.h"
PlayerDashingState::PlayerDashingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::dashing);
	player->SetTimeBuffer(0);
	player->SetVelocityX(VELOCITY_X * 3);
	this->current_state = PlayerState::NameState::dashing;
	IsDucking = false;
	IsGong = false;
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

void PlayerDashingState::Render()
{
}
//Perfect, không được sửa nữa
void PlayerDashingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
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
		player->ChangeState(new PlayerRunningState());
		return;
	}
	else {
		if (player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight && keyboard->KeyUp(RIGHT_KEY)) {
			player->GetCurrentAnimation()->SetAnimationTime(0.0f);
			player->GetCurrentAnimation()->ResetAnimation();
			player->ChangeState(new PlayerRunningState());
			return;
		}
		if (player->GetMoveDirection() == Entity::Entity_Direction::RightToLeft && keyboard->KeyUp(LEFT_KEY)) {
			player->GetCurrentAnimation()->SetAnimationTime(0.0f);
			player->GetCurrentAnimation()->ResetAnimation();
			player->ChangeState(new PlayerRunningState());
			return;
		}
	}
		


}
