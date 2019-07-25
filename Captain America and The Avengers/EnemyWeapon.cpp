#include "EnemyWeapon.h"



void EnemyWeapon::Update(float dt)
{
	Entity::Update(dt);
}

EnemyWeapon::EnemyWeapon()
{
	this->explode_ani = NULL;
}


EnemyWeapon::~EnemyWeapon()
{
	delete this->explode_ani;
}
