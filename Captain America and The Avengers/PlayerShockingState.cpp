#include "PlayerShockingState.h"
#include "Framework//Debug.h"
#include "Shield.h"
#include "PlayerBeatenState.h"
PlayerShockingState::PlayerShockingState(int damage)
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::shocking);
	this->current_state = PlayerState::NameState::shocking;
	player->SetVelocity(0, 0);
	this->time_shocking = 0;
	player->OnTheWater = true;
	player->time_invisible = TIME_INVISIBLE;
	this->damage = damage;
	player->OnTheWater = true;

}
PlayerShockingState::~PlayerShockingState()
{

}

void PlayerShockingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	this->time_shocking += dt;
	if (player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
		player->SetPositionX(player->GetPosition().x - VELOCITY_X * dt * 2 / 3);

	}
	else
	{
		player->SetPositionX(player->GetPosition().x + VELOCITY_X * dt * 2 / 3);
	}
	if (time_shocking > TIME_SHOCKING || player->IsCollisionWithGround(dt))
	{
		player->ChangeState(new PlayerBeatenState(this->damage));
		return;
	}
	if (player->IsCollisionWithGround(dt) == false)
	{
		player->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
		player->SetVelocityY(VELOCITY_Y*1.5);
		return;
	}
}

void PlayerShockingState::Draw()
{
}

BoundingBox PlayerShockingState::GetBoundingBox()
{
	Player * player = Player::GetInstance();
	return BoundingBox(
		player->GetPosition(),
		player->GetSize(),
		player->GetVelocityX(),
		player->GetVelocityY()
	);

}

void PlayerShockingState::HandleInput(float dt)
{

}
