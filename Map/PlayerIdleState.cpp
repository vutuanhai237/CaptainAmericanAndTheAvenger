#include "PlayerIdleState.h"
#include "Framework//Debug.h"
PlayerIdleState::PlayerIdleState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::idle);
	player->SetIsThrowing(false);
	player->SetIsRolling(false);
	this->current_state = PlayerState::NameState::idle;
	//player->SetPositionIdle(player->GetPosition());
	//D3DXVECTOR2 idle_position = player->GetPositionIdle();
	//player->SetPositionY(idle_position.y);
	player->SetPositionIdle(player->GetPosition());

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

void PlayerIdleState::Render()
{
}

void PlayerIdleState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (player->IsCollisionWithGround(dt).side == CollisionSide::none)
	{
		player->ChangeState(new PlayerJumpingDownState());
		return;
	}
		




	// Nếu ấn X thì nhảy
	if (keyboard->KeyDown(JUMP_KEY)) {
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	if (keyboard->KeyDown(ATTACK_KEY)) {
		player->ChangeState(new PlayerThrowingState());
		return;
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
