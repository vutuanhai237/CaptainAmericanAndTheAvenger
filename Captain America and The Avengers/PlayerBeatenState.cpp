#include "PlayerBeatenState.h"
#include "Framework/SoundManager.h"
#include "Shield.h"
#include "PlayerDieState.h"
PlayerBeatenState::PlayerBeatenState(int damage)
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::beaten);
	this->current_state = PlayerState::NameState::beaten;
	player->SetVelocity(0, 0);
	this->time_beaten = 0;
	player->OnTheWater = true;
	player->time_invisible = TIME_INVISIBLE;
	player->hp -= damage;
	player->OnTheWater = true;
	SoundManager::GetInstance()->Play(SoundManager::SoundList::enemy_fire);
}
PlayerBeatenState::~PlayerBeatenState()
{

}

void PlayerBeatenState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	this->time_beaten += dt;
	if (player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
		player->SetPositionX(player->GetPosition().x - VELOCITY_X*dt*1/3);

	}
	else
	{
		player->SetPositionX(player->GetPosition().x + VELOCITY_X * dt*1/3);
	}
	if (time_beaten > TIME_BEATEN_MIN && player->hp > 0)
	{
		if (player->IsCollisionWithGround(dt) || player->IsCollisionWithSpike(dt)) {
			player->ChangeState(new PlayerIdleState());
			return;
		}
	
	}
	if (player->IsCollisionWithGround(dt) == false) 
	{
		player->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
		player->SetVelocityY(VELOCITY_Y*1.5);
		return;
	}


}

void PlayerBeatenState::Draw()
{
}

BoundingBox PlayerBeatenState::GetBoundingBox()
{
	Player * player = Player::GetInstance();
	return BoundingBox(
		player->GetPosition(),
		player->GetSize(),
		player->GetVelocityX(),
		player->GetVelocityY()
	);

}

void PlayerBeatenState::HandleInput(float dt)
{
	Player *player = Player::GetInstance();
	if (player->hp <= 0) {
		if (player->IsCollisionWithGround(dt, 8) 
			|| player->IsCollisionWithWall(dt)
			|| player->IsCollisionWithSpike(dt))
		{
			player->ChangeState(new PlayerDieState());
			return;
		}
		else {
			player->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
			player->SetVelocityY(VELOCITY_Y*1.5);
			return;
		}
		return;
		
	}
	if (player->IsCollisionWithWall(dt))
	{
		player->ChangeState(new PlayerJumpingDownState());
		return;
	}

	if (player->IsCollisionWithGround(dt, 8))
	{
		player->ChangeState(new PlayerJumpingDownState());
		return;
	}

	if (player->IsCollisionWithSpike(dt, 8))
	{
		player->ChangeState(new PlayerIdleState());
		return;
	}
	if (player->IsCollisionWithWater(dt, 8))
	{
		player->ChangeState(new PlayerJumpingDownState());
		return;
	}
}
