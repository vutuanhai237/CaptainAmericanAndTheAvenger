#include "PlayerIdleState.h"
#include "PlayerRollingState.h"
#include "PlayerFlowingState.h"
#include "PlayerShieldDownState.h"
#include "Framework//Debug.h"
#include "Shield.h"
#include "ShieldOnAirState.h"

PlayerJumpingDownState::PlayerJumpingDownState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::jumping_down);
	player->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
	this->current_state = PlayerState::NameState::jumping_down;
	this->animation_before_flowing = new Animation(-1, L"Resources//CaptainState//CaptainBeforeFlowing.png", D3DCOLOR_XRGB(255, 0, 255), 7);
	this->animation_before_flowing->SetTime(0.25);
	this->IsDuocChuyenState = false;
	this->IsDuocChuyenAnimation = false;
	this->time_animation_before_flowing = 0;
	player->SetVelocityX(0);
	player->IsJumpingDown == false;
	player->IsRolling = false;
	player->IsOnAir = true;
	// Khi từ đá chuyển về nhảy thì mới có quyền đá tiếp
	player->time_kicking = 0;
	Shield::GetInstance()->SetShieldState(new ShieldOnAirState());

}
PlayerJumpingDownState::~PlayerJumpingDownState()
{

}

void PlayerJumpingDownState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	if (player->GetVelocityY() >= -VELOCITY_Y) {
		player->SetVelocityY(abs(player->GetVelocityY()) + JUMPING_ACCELERATION);
	}
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

	if (player->IsCollisionWithGround(dt, 8))
	{	
		player->ChangeState(new PlayerDuckingState());
		return;
	}
	if (IsDuocChuyenState) {
		player->ChangeState(new PlayerFlowingState());
		return;
	}

	if (player->IsCollisionWithWater(dt, 0))
	{
 		IsDuocChuyenAnimation = true;
		
		player->SetCurrentAnimation(this->animation_before_flowing);
		player->OnTheWater = true;
		player->SetVelocityY(VELOCITY_Y / 20);
	}
	
	if (IsDuocChuyenAnimation) {
		this->time_animation_before_flowing += dt;
		player->GetCurrentAnimation()->SetFrame(player->GetCurrentAnimation()->GetNumberCurrentFrame() + 1);
		if (player->GetCurrentAnimation()->GetNumberCurrentFrame() == 7) {
			IsDuocChuyenState = true;
		}
	}

	if (keyboard->KeyDown(ATTACK_KEY)) {
		player->ChangeState(new PlayerKickingState());
		return;
	}
	
	if (keyboard->KeyDown(DOWN_KEY) && player->IsShieldDown) {
		player->ChangeState(new PlayerShieldDownState());
		return;
	}
	if (!keyboard->KeyPress(RIGHT_KEY) && !keyboard->KeyPress(LEFT_KEY)) {
		return;
	}
	// Đang ở trên không, nếu ấn left thì dịch qua trái
	if (keyboard->KeyPress(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - DELTA_JUMP * dt);
	}
	// Đang ở trên không, nếu ấn left thì dịch qua phải
	if (keyboard->KeyPress(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + DELTA_JUMP * dt);

	}

	
}
