#include "LaserBullet.h"
#include "FrameWork//Debug.h"
#include "SceneManager.h"
#include "PlayerBeatenState.h"
#include "BossWizard.h"

void LaserBullet::Update(float dt)
{
	EnemyWeapon::Update(dt);
	if (this->e != NULL) {
		this->SetPositionY(this->e->GetYFromX(this->GetPosition().x));
	}
	this->distance += abs(this->GetVelocityX()*dt);
	this->IsComeBack = true;
}

int LaserBullet::OnCollision(Entity* obj, float dt)
{
	if (this->IsDead == true) {
		return 1;
	}
	if (obj->GetType() == Entity::Entity_Type::player_weapon_type
		&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
	{

		if (IsComeBack) {
			this->SetVelocityX(100.0f);
			this->IsComeBack = false;
			e = new Equation(
				this->position,
				D3DXVECTOR2(this->position.x + (this->GetMoveDirection() == Entity::Entity_Direction::LeftToRight ? -1 : 1) * 30, this->position.y + 5));
			if (Player::GetInstance()->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
				this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
			}
			if (Player::GetInstance()->GetMoveDirection() == Entity::Entity_Direction::RightToLeft) {
				this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			}

		}
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

void LaserBullet::Draw()
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

LaserBullet::LaserBullet(D3DXVECTOR2 position, Entity::Entity_Direction direction)
{
	this->SetTag(Entity::Entity_Tag::boss_bullet);
	this->SetType(Entity::Entity_Type::enemy_weapon_type);
	this->current_ani = new Animation(13, 1);
	this->SetVelocityX(LASER_BULLET_VELOCITY_X);
	this->size.cx = 5; this->size.cy = 5;
	this->SetPosition(position);
	this->IsLocking = true;
	this->distance = 0;
	this->IsDead = false;
	this->SetMoveDirection(direction);
	this->e = NULL;
}


LaserBullet::~LaserBullet()
{
}
