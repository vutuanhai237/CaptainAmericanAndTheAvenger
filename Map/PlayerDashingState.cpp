#include "PlayerDashingState.h"
#include "PlayerIdleState.h"
#include "Framework//Debug.h"
PlayerDashingState::PlayerDashingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::dashing);
	player->SetTimeBuffer(0);
	player->SetVelocityX(VELOCITY_X * 3);
	player->SetSize(4 >> 3, 3 >> 3);
	this->current_state = PlayerState::NameState::dashing;


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

void PlayerDashingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	// Chỉ hiển thị 1 sprite đầu khi dashing, còn lại giữ nguyên sprite 2
	if (player->GetCurrentAnimation()->GetNumberCurrentFrame() == 2)
	{
		player->GetCurrentAnimation()->Pause(0.016f * 18.0f);
	}
	// Dừng dashing khi time out hoặc thả nút left/right
	if (player->GetCurrentAnimation()->GetAnimationTime() >= 0.016f * 20.0f || keyboard->KeyUp(RIGHT_KEY))
	{
		if (keyboard->KeyPress(LEFT_KEY)) {
			goto LEFT;
		}
		player->GetCurrentAnimation()->ResetAnimation();
		// Nếu vẫn còn giữ phím right thì chuyển sang running
		if (keyboard->KeyPress(RIGHT_KEY)) {
			player->ChangeState(new PlayerRunningState());
			return;
		}
		// Không ấn gì nữa thì idle
		player->ChangeState(new PlayerIdleState());
		return;
	}

	if (player->GetCurrentAnimation()->GetAnimationTime() >= 0.016f * 20.0f || keyboard->KeyUp(LEFT_KEY))
	{
		player->GetCurrentAnimation()->ResetAnimation();
		// Nếu vẫn còn giữ phím left thì chuyển sang running
		if (keyboard->KeyPress(LEFT_KEY)) {
		LEFT:
			player->ChangeState(new PlayerRunningState());
			return;
		}
		player->ChangeState(new PlayerIdleState());
		return;
	}


	if (player->GetMoveDirection() == Entity::Entity_Direction::RightToLeft)
	{
		return;
	}
	if (player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight)
	{
		return;
	}
	//player->GetCurrentAnimation()->ResetAnimation();
	//player->ChangeState(new PlayerIdleState());

}
