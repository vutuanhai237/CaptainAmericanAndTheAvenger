#include "EnergyBullet.h"
#include "FrameWork//Debug.h"
#include "SceneManager.h"
#include "BossWizard.h"
#include "PlayerBeatenState.h"
void EnergyBullet::Update(float dt)
{
	EnemyWeapon::Update(dt);
	this->distance += abs(this->GetVelocityX()*dt);
}

int EnergyBullet::OnCollision(Entity* obj, float dt)
{
	if (this->IsDead == true) {
		return 1;
	}
	if (obj->GetType() == Entity::Entity_Type::player_weapon_type
		&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
	{
		this->SetVelocityX(0.0f);
		this->SetVelocityY(ENERGY_BULLET_VELOCITY_X);
		return 0;
	}
	Player *player = Player::GetInstance();
	if (obj->GetType() == Entity::Entity_Type::player_type
		&& player->time_invisible <= 0
		&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
	{
		player->ChangeState(new PlayerBeatenState());
		return 1;
	}
	return 0;
}

void EnergyBullet::Draw()
{
	if (this->GetVelocityX() != 0) {
		this->current_ani->Draw(this->GetPosition());
		if (BossWizard::GetInstance()->GetMoveDirection()) {
			this->current_ani->SetScale(1, 1);
		}
		else {
			this->current_ani->SetScale(-1, 1);
		}
	}
}

EnergyBullet::EnergyBullet(D3DXVECTOR2 position, Entity::Entity_Direction direction)
{
	this->SetTag(Entity::Entity_Tag::boss_bullet);
	this->SetType(Entity::Entity_Type::enemy_weapon_type);
	this->horizontal_ani = new Animation(EnergyBulletType::horizontal, 1);
	this->vertical_ani = new Animation(EnergyBulletType::vertical, 1);
	this->crossed_ani = new Animation(EnergyBulletType::crossed, 1);
	this->current_ani = this->horizontal_ani;
	this->SetVelocityX(ENERGY_BULLET_VELOCITY_X);
	this->size.cx = 5; this->size.cy = 5;
	this->SetPosition(position);
	this->IsLocking = true;
	this->distance = 0;
	this->IsDead = false;
	this->SetMoveDirection(direction);
}


EnergyBullet::~EnergyBullet()
{
}