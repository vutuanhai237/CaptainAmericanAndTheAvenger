#include "EnemyWeapon.h"
#include "SceneManager.h"
#include "Collision.h"

void EnemyWeapon::Update(float dt)
{
	Entity::Update(dt);
}

int EnemyWeapon::OnCollision(Entity *, float dt)
{
	return 0;
}

EnemyWeapon::EnemyWeapon() : Entity()
{
	this->explode_ani = NULL;
	this->type = Entity::Entity_Type::enemy_weapon_type;
}

EnemyWeapon::~EnemyWeapon()
{
	delete this->explode_ani;
}

bool EnemyWeapon::IsCollisionExplode()
{
	std::vector<Entity*> *objs = SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();
	Collision *Checker = Collision::getInstance();
	CollisionOut out;
	for (Entity *item : *objs)
	{
		switch (item->GetTag())
		{
		case Entity::Entity_Tag::ground:
		case Entity::Entity_Tag::wall:
		case Entity::Entity_Tag::spike:
			if (Checker->IsCollide(this->GetBoundingBox(), item->GetBoundingBox()))
			{
				return true;
			}
			break;
		default:
			break;
		}
	}
	return false;
}