#include "Bullet.h"
#include "FrameWork/SoundManager.h"
#include "SceneManager.h"
#include "PlayerBeatenState.h"
#include "Shield.h"

void Bullet::Update(float dt)
{
	EnemyWeapon::Update(dt);
}

int Bullet::OnCollision(Entity* obj, float dt)
{
	if (EnemyWeapon::IsCollisionExplode()) 
	{
		return 1;
	}
	Player *player = Player::GetInstance();
	if (obj->GetTag() == Entity::Entity_Tag::shield && player->time_invisible < 0.016*5)
	{
		// Change direction while collision with shield
		if (Shield::GetInstance()->GetShieldState()->GetCurrentState() == ShieldState::NameState::Nomal && Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
		{
			SoundManager::GetInstance()->Play(SoundManager::SoundList::shield_collision);
			if (this->velocity.y == 0) 
			{
				this->jump_direction = Entity::Entity_Jump_Direction::BotToTop;
				this->velocity.y = abs(this->velocity.x);
				this->velocity.x = 0.0f;
			}
			else
			{
				if (this->direction == Entity::Entity_Direction::LeftToRight) 
				{
					this->direction = Entity::Entity_Direction::RightToLeft;
				}
				else
				{
					this->direction = Entity::Entity_Direction::LeftToRight;
				}
			}
			return 0;
		}
	}
	else
	{
		if (obj->GetType() == Entity::Entity_Type::player_type && player->time_invisible <= 0 && Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox())) 
		{
			player->ChangeState(new PlayerBeatenState(BULLET_DAMAGE));
			return 1;
		}
	}
	return 0;
}

void Bullet::Draw()
{
	this->current_ani->Draw(this->GetPosition());
}

Bullet::Bullet(D3DXVECTOR2 position, Entity::Entity_Direction direction, FLOAT direction_y) : EnemyWeapon()
{
	this->SetTag(Entity::Entity_Tag::soldier_bullet);
	this->SetType(Entity::Entity_Type::enemy_weapon_type);
	// Animation zone
	this->current_ani = new Animation(12, 1);
	// properties zone
	this->direction = direction;
	this->velocity.x = 200.0f;
	this->velocity.y = direction_y;
	this->size.cx = this->size.cy = 2;
	this->SetPosition(position);
	this->SetMoveDirection(direction);
	this->damage = BULLET_DAMAGE;
	this->distance = 0;
	this->IsDead = false;
	this->IsLocking = true;
	if (direction_y > 0) 
	{
		this->jump_direction = Entity::Entity_Jump_Direction::BotToTop;
	}
	else
	{
		this->jump_direction = Entity::Entity_Jump_Direction::TopToBot;
	}
	SoundManager::GetInstance()->Play(SoundManager::SoundList::enemy_fire);
}

Bullet::~Bullet()
{
}
