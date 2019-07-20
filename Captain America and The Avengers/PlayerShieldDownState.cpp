#include "PlayerShieldDownState.h"
#include "Framework//Debug.h"
#include "PlayerFlowingState.h"
#include "Shield.h"
#include "ShieldDownState.h"

PlayerShieldDownState::PlayerShieldDownState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::shield_down);
	player->SetTimeBuffer(0);
	this->current_state = PlayerState::NameState::shield_down;
	player->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
	player->SetVelocityY(VELOCITY_Y);


	Shield::GetInstance()->SetShieldState(new ShieldDownState());
}
PlayerShieldDownState::~PlayerShieldDownState()
{

}

void PlayerShieldDownState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
}

void PlayerShieldDownState::Draw()
{

}

void PlayerShieldDownState::Render()
{
}

void PlayerShieldDownState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	player->time_air_jumping += dt;
	player->time_air_rolling += dt;

	if (player->IsCollisionWithGround(dt, 16))
	{
		player->SetVelocityY(0);
		if (keyboard->KeyPress(DOWN_KEY)) {
			return;
		}
		else {
			player->ChangeState(new PlayerIdleState());
			return;
		}
	}
	if (player->IsCollisionWithWater(dt, 16))
	{
		player->SetVelocityY(0);
		player->OnTheWater = true;
		if (keyboard->KeyPress(DOWN_KEY)) {
			return;
		}
		else {
			
			player->ChangeState(new PlayerJumpingDownState());
			return;
		}
		return;
	}
	if (keyboard->KeyPress(LEFT_KEY) && player->OnTheWater == false) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - DELTA_JUMP * dt);
	}
	// Đang ở trên không, nếu ấn left thì dịch qua phải
	if (keyboard->KeyPress(RIGHT_KEY) && player->OnTheWater == false) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + DELTA_JUMP * dt);
	}
	if (!keyboard->KeyPress(DOWN_KEY)) {
		if (player->time_air_rolling < TIME_ROLLING && player->GetPreviousState() == PlayerState::NameState::rolling) {
			player->ChangeState(new PlayerRollingState());
			return;
		}
		if (player->GetPreviousState() == PlayerState::NameState::jumping_down) {
			player->ChangeState(new PlayerJumpingDownState());
			return;
		}
		
	}
	else {
		return;
	}
	player->ChangeState(new PlayerJumpingDownState());
	return;
}
