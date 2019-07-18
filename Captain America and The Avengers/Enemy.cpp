#include "Enemy.h"

void Enemy::Update(float dt)
{
	Entity::Update(dt);

}

void Enemy::Spawn()
{
}

void Enemy::SetSpawnBox(float top, float left, float width, float height, Entity::Entity_Direction direction)
{
	this->spawn_box.top = top;
	this->spawn_box.left = left;
	this->spawn_box.bot = top-height;
	this->spawn_box.right = left + width;
	this->direction = direction;
}

void Enemy::SetBoxCollider(BoxCollider box)
{
	this->box = box;
}


Enemy::Enemy()
{
	this->explode_ani = new Animation(1, L"Resources//Enemy//Explode.png", D3DCOLOR_XRGB(255, 0, 255), 3);
}


Enemy::~Enemy()
{
}
