#include "EnemyWeapon.h"



void EnemyWeapon::Update(float dt)
{
	Entity::Update(dt);
}

int EnemyWeapon::OnCollision(Entity *, float dt)
{
	return 0;
}

EnemyWeapon::EnemyWeapon()
{
	this->explode_ani = NULL;
}


EnemyWeapon::~EnemyWeapon()
{
	delete this->explode_ani;
}
