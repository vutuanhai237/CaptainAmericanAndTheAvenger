#include "PlayerKickingState.h"
#include "PlayerIdleState.h"
#include "PlayerRollingState.h"
#include "Framework/SoundManager.h"
#include "Shield.h"
#include "ShieldKickState.h"
#include "PlayerJumpingDownState.h"
#include "SceneManager.h"
#include "PlayerLeg.h"

PlayerKickingState::PlayerKickingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::kicking);
	this->current_state = PlayerState::NameState::kicking;
	Shield::GetInstance()->SetShieldState(new ShieldKickState());
	SoundManager::GetInstance()->Play(SoundManager::SoundList::player_punch_kick);
	SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(new PlayerLeg());
}
PlayerKickingState::~PlayerKickingState()
{

}

void PlayerKickingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->time_kicking += dt;
	player->time_air_jumping += dt;
	if (player->time_kicking >= TIME_KICKING)
	{
		if (player->GetPreviousState() == PlayerState::NameState::jumping)
		{
			player->ChangeState(new PlayerJumpingState());
			return;
		}
		if (player->GetPreviousState() == PlayerState::NameState::jumping_down)
		{
			player->ChangeState(new PlayerJumpingDownState());
			return;
		}
		if (player->GetPreviousState() == PlayerState::NameState::rolling)
		{
			player->ChangeState(new PlayerRollingState());
			return;
		}	
	}
	if (player->GetPreviousState() == PlayerState::NameState::rolling || player->time_air_jumping >= TIME_AIR )
	{
		player->SetVelocityY(player->GetVelocityY() - ROLLING_ACCELERATION);
	}
}

void PlayerKickingState::Draw()
{

}

BoundingBox PlayerKickingState::GetBoundingBox()
{
	Player * player = Player::GetInstance();
	return BoundingBox(
		player->GetPosition(),
		player->GetSize(),
		player->GetVelocityX(),
		player->GetVelocityY()
	);
}

void PlayerKickingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (player->IsCollisionWithGround(dt, 6))
	{
		player->ChangeState(new PlayerIdleState());
		return;
	}

	if (player->IsCollisionWithWater(dt, 0))
	{
		player->ChangeState(new PlayerJumpingDownState());
		player->SetPositionY(player->GetPosition().y + 10);
		return;
	}
	// Đang ở trên không, nếu ấn left thì dịch qua trái
	if (keyboard->KeyPress(LEFT_KEY))
	{
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - DELTA_JUMP*dt);
		return;
	}
	// Đang ở trên không, nếu ấn left thì dịch qua phải
	if (keyboard->KeyPress(RIGHT_KEY)) 
	{
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + DELTA_JUMP * dt);
		return;
	}
}
