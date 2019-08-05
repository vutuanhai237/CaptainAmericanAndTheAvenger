#include "TurretBullet.h"
#include "FrameWork/SoundManager.h"
#include "SceneManager.h"
#include "PlayerBeatenState.h"
#include "Shield.h"

void TurretBullet::Update(float dt)
{
	EnemyWeapon::Update(dt);
}

int TurretBullet::OnCollision(Entity* obj, float dt)
{
	if (EnemyWeapon::IsCollisionExplode())
	{
		return 1;
	}

	if (obj->GetTag() == Entity::Entity_Tag::shield)
	{
		if (Shield::GetInstance()->GetShieldState()->GetCurrentState() == ShieldState::NameState::Nomal && Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
		{
			SoundManager::GetInstance()->Play(SoundManager::SoundList::shield_collision);
			if (abs((int)this->velocity.y) % 180 < 10) // bay thang
			{
				this->jump_direction = Entity::Entity_Jump_Direction::BotToTop;
				this->velocity.y = abs(this->velocity.x);
				this->velocity.x = 0.0f;
			}
			else
			{
				if (this->direction == Entity::Entity_Direction::LeftToRight)
					this->direction = Entity::Entity_Direction::RightToLeft;
				else
					this->direction = Entity::Entity_Direction::LeftToRight;
			}
			return 0;
		}
	}
	else
	{
		Player *player = Player::GetInstance();
		if (obj->GetType() == Entity::Entity_Type::player_type)
		{
			if (player->time_invisible <= 0
				&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
			{
				player->ChangeState(new PlayerBeatenState(TURRET_BULLET_DAMAGE));
				return 1;
			}
		}
			
	}
	return 0;
}

void TurretBullet::Draw()
{
	this->current_ani->Draw(this->GetPosition());
}

TurretBullet::TurretBullet(D3DXVECTOR2 position, Entity::Entity_Direction direction, int alpha): EnemyWeapon()
{
	this->SetTag(Entity::Entity_Tag::soldier_bullet);
	this->SetType(Entity::Entity_Type::enemy_weapon_type);
	this->current_ani = new Animation(31, 1);

	this->velocity.x = -TURRET_BULLET_VELOCITY * cos(alpha*PI/180);
	this->velocity.y = TURRET_BULLET_VELOCITY * sin(alpha*PI/180);
	if (this->velocity.y > 0)
		this->jump_direction = Entity::Entity_Jump_Direction::BotToTop;
	else
		this->jump_direction = Entity::Entity_Jump_Direction::TopToBot;
	if (this->velocity.x > 0)
		Entity::direction = Entity::Entity_Direction::LeftToRight;
	else
		Entity::direction = Entity::Entity_Direction::RightToLeft;

	this->size.cx = 5; this->size.cy = 5;
	this->SetPosition(position);
	this->IsLocking = true;
	this->distance = 0;
	this->IsDead = false;
	this->damage = TURRET_BULLET_DAMAGE;
	SoundManager::GetInstance()->Play(SoundManager::SoundList::enemy_fire);

}


TurretBullet::~TurretBullet()
{
}
