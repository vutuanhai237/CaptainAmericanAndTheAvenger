#include "PlayerShieldDownState.h"
#include "Framework//Debug.h"
PlayerShieldDownState::PlayerShieldDownState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::shield_down);
	player->SetTimeBuffer(0);
	this->current_state = PlayerState::NameState::shield_down;


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
	if (player->IsCollisionWithGround(dt, 8) && player->IsLockCollision == false)
	{
		player->ChangeState(new PlayerShieldDownState());
		player->IsLockCollision == true;
	}
	if (!keyboard->KeyPress(DOWN_KEY)) {
		if (player->GetPreviousState() == PlayerState::NameState::rolling) {
			player->ChangeState(new PlayerRollingState());
			return;
		}
		if (player->GetPreviousState() == PlayerState::NameState::jumping_down) {
			player->ChangeState(new PlayerJumpingDownState());
			return;
		}
		
	}
	if (keyboard->KeyPress(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - DELTA_JUMP * dt);
	}
	// Đang ở trên không, nếu ấn left thì dịch qua phải
	if (keyboard->KeyPress(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + DELTA_JUMP * dt);
	}
	player->ChangeState(new PlayerIdleState());
	return;
}
