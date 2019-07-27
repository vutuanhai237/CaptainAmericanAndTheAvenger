#include "Bullet.h"
#include "FrameWork//Debug.h"
#include "SceneManager.h"
#include "PlayerBeatenState.h"
void Bullet::Update(float dt)
{
	EnemyWeapon::Update(dt);
	this->distance += abs(this->GetVelocityX()*dt);

}

int Bullet::OnCollision(Entity* obj, float dt)
{
	if (this->IsDead == true) {
		return 1;
	}
	Player *player = Player::GetInstance();
	if (obj->GetType() == Entity::Entity_Type::player_type 
		&& player->time_invisible <= 0
		&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
	{
			player->ChangeState(new PlayerBeatenState());
			return 1;
	}
	if (obj->GetType() == Entity::Entity_Type::player_weapon_type
		&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
	{
		
		return 0;
	}




	return 0;

}

void Bullet::Draw()
{
	if (this->GetVelocityX() != 0) {
		this->current_ani->Draw(this->GetPosition());
	}
}

Bullet::Bullet(D3DXVECTOR2 position, Entity::Entity_Direction direction)
{
	this->SetTag(Entity::Entity_Tag::red_rocket);
	this->SetType(Entity::Entity_Type::enemy_weapon_type);
	this->current_ani = new Animation(12, 1);
	this->SetVelocityX(200);
	this->size.cx = 5; this->size.cy = 5;
	this->SetPosition(position);
	this->IsLocking = true;
	this->distance = 0;
	this->IsDead = false;
	this->SetMoveDirection(direction);
}


Bullet::~Bullet()
{
}
