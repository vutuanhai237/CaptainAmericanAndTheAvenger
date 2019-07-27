#include "Enemy.h"
#include "PlayerBeatenState.h"
Animation * Enemy::GetCurrentAnimation()
{
	return this->current_animation;
}

void Enemy::Update(float dt)
{
	Entity::Update(dt);

}

int Enemy::OnCollision(Entity* obj, float dt)
{
	Player *player = Player::GetInstance();
	if (obj->GetType() == Entity::Entity_Type::player_type 
		&& player->time_invisible < 0
		&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox())) 
	{
		if (this->time_beaten == 0) {
			this->time_beaten = ENEMY_TIME_BEATEN;

		}
		if (player->GetCurrentState() != PlayerState::shield_down) {
			player->ChangeState(new PlayerBeatenState());

		}
	}

	return 0;
}

void Enemy::Spawn()
{
}



Enemy::Enemy()
{
	Entity::type = Entity_Type::enemy_type;
	this->explode_ani = new Animation(1, L"Resources//Enemy//Explode.png", D3DCOLOR_XRGB(255, 0, 255), 3);
	this->IsLocking = true;
	this->jump_direction= Entity::Entity_Jump_Direction::TopToBot;
}


Enemy::~Enemy()
{
}

bool Enemy::IsCollisionWithGround(float dt, int delta_y)
{
	return false;
}