#include "PlayerFlowingState.h"
#include "PlayerDivingState.h"
#include "FrameworK/SoundManager.h"
PlayerFlowingState::PlayerFlowingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::flowing);
	this->current_state = PlayerState::NameState::flowing;
	player->SetTimeBuffer(0);
	player->SetPositionY(34.0f);
	player->SetVelocity(0, 0);
	player->time_air_jumping = 0;
	player->time_kicking = 0;
	player->time_air_rolling = 0;
	player->time_ducking_before_idle = 0;
	player->time_jumping_before_flowing = 0;
	player->time_don_tho = 0;
	player->IsJumpingDown = false;
	player->IsJumping = false;
	player->OnTheWater = true;

}
PlayerFlowingState::~PlayerFlowingState()
{

}

void PlayerFlowingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->SetPositionX(player->GetPosition().x - VELOCITY_X / 2 * dt);
}

BoundingBox PlayerFlowingState::GetBoundingBox()
{
	Player *player = Player::GetInstance();
	SIZE size; size.cx = (LONG)(-0.0f); size.cy = (LONG)(-0.0f);
	D3DXVECTOR2 pos = player->GetPosition();
	return BoundingBox(pos, size, player->GetVelocityX(), player->GetVelocityY());
}

void PlayerFlowingState::Draw()
{

}

void PlayerFlowingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (keyboard->KeyDown(JUMP_KEY)) 
	{
		SoundManager::GetInstance()->Play(SoundManager::SoundList::player_diving);
		player->ChangeState(new PlayerJumpingState());
		player->OnTheWater = false;
		return;
	}
	if (keyboard->KeyPress(RIGHT_KEY) && keyboard->KeyPress(DOWN_KEY))
	{
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + DELTA_JUMP * dt);
		player->GetCurrentAnimation()->Continue();
		return;
	}
	if (keyboard->KeyPress(LEFT_KEY) && keyboard->KeyPress(DOWN_KEY))
	{
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - DELTA_JUMP * dt);
		player->GetCurrentAnimation()->Continue();
		return;
	}
	if (keyboard->KeyPress(RIGHT_KEY))
	{
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + DELTA_JUMP * dt);
		player->GetCurrentAnimation()->Continue();
		return;
	}
	if (keyboard->KeyPress(LEFT_KEY))
	{
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - DELTA_JUMP * dt);
		player->GetCurrentAnimation()->Continue();
		return;
	}
	if (keyboard->KeyPress(DOWN_KEY))
	{
		player->SetCurrentAnimation(player->GetAnimation(PlayerState::NameState::diving));
		player->GetCurrentAnimation()->SetFrame(1);
		player->ChangeState(new PlayerDivingState());
		return;
	}
	player->GetCurrentAnimation()->SetFrame(1);
	player->GetCurrentAnimation()->Stop();
}
