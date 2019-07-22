#include "EnemyWeapon.h"



void EnemyWeapon::Update(float dt)
{
	Entity::Update(dt);
}

EnemyWeapon::EnemyWeapon()
{
	this->explode_ani = new Animation(1, L"Resources//Enemy//RedRocketRobot//RedRocketCrossed.png", D3DCOLOR_XRGB(255, 0, 255), 2);
}


EnemyWeapon::~EnemyWeapon()
{
	delete this->explode_ani;
}
