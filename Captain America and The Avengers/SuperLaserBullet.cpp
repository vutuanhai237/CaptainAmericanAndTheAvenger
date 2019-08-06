#include "SuperLaserBullet.h"
#include "FrameWork/SoundManager.h"
#include "SceneManager.h"
#include "PlayerBeatenState.h"

void SuperLaserBullet::Update(float dt)
{
	EnemyWeapon::Update(dt);
	this->current_ani->Update(dt);
	if (this->IsExploding) 
	{
		this->Exploding(dt);
		return;
	}
}

int SuperLaserBullet::OnCollision(Entity* obj, float dt)
{
	if (this->IsDead == true) 
	{
		return 1;
	}
	Player *player = Player::GetInstance();
	if (obj->GetType() != Entity::Entity_Type::player_type)
		return 0;
	if (player->time_invisible <= 0 
		&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
	{
		player->ChangeState(new PlayerBeatenState(SUPER_LASER_BULLET_DAMAGE));
		if (this->IsExploding == false) 
		{
			this->Release();
			this->IsExploding = true;
			SoundManager::GetInstance()->Play(SoundManager::SoundList::entity_explode);
		}
	}
	return 0;
}

void SuperLaserBullet::Exploding(float dt)
{
	this->SetVelocityX(1);
	if (this->time_out_explode == 0) 
	{
		this->current_ani = this->explode_ani;
	}
	this->time_out_explode += dt;
	if (this->time_out_explode > TIME_EXPLODE) 
	{
		this->IsDead = true;
	}
}

void SuperLaserBullet::Release()
{
	this->distance = 0;
	this->IsStraight = true;
	this->time_out_straight = 0;
	this->time_out_explode = 0;
}

void SuperLaserBullet::Draw()
{
	if (this->GetVelocityX() != 0) {
		if (this->GetMoveDirection()) {
			this->current_ani->SetScale(1, 1);
		}
		else {
			this->current_ani->SetScale(-1, 1);
		}
		this->current_ani->Draw(this->GetPosition());
	}
}

SuperLaserBullet::SuperLaserBullet(D3DXVECTOR2 position, Entity::Entity_Direction direction)
{
	this->SetTag(Entity::Entity_Tag::red_rocket);
	this->SetType(Entity::Entity_Type::enemy_weapon_type);
	// Animation zone
	this->explode_ani = new Animation(7, 3);
	this->explode_ani->SetTime(0.083f, 10000.0f);
	this->current_ani = new Animation(28, 1);
	// properties zone
	this->IsLocking = true;
	this->IsStraight = true;
	this->IsDead = false;
	this->IsExploding = false;
	this->time_out_straight = 0;
	this->distance = 0;
	this->size.cx = 13; this->size.cy = 5;
	this->SetPosition(position);
	this->SetVelocityX(SUPER_LASER_BULLET_VELOCITY_X);
	this->SetMoveDirection(direction);
	this->damage = SUPER_LASER_BULLET_DAMAGE;
	SoundManager::GetInstance()->Play(SoundManager::SoundList::boss_moving_firing);
}


SuperLaserBullet::~SuperLaserBullet()
{

}
