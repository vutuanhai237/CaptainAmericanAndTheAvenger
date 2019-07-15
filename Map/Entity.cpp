#include "Entity.h"



Entity::Entity()
{
	tag = none;
}


Entity::~Entity()
{
}

void Entity::SetActive(bool _IsActive)
{
	this->IsActive = _IsActive;
}

bool Entity::GetActive()
{
	return this->IsActive;
}

void Entity::SetTag(Entity_Tag _tag)
{
}

Entity::Entity_Tag Entity::GetTag()
{
	return this->tag;
}

void Entity::SetType(Entity_Type _type)
{
	this->type = _type;
}

Entity::Entity_Type Entity::GetType()
{
	return this->type;
}

void Entity::SetStatic(bool _IsStatic)
{
	this->IsStatic = _IsStatic;
}

void Entity::SetAliveState(Entity_AliveState _alive)
{
	this->alive_state = _alive;
}

void Entity::SetVelocity(D3DXVECTOR2 _velocity)
{
}

void Entity::SetVelocity(float x, float y)
{
	this->velocity.x = x;
	this->velocity.y = y;
}


void Entity::SetPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
}

D3DXVECTOR2 Entity::GetPosition()
{
	return this->position;
}

D3DXVECTOR2 Entity::GetVelocity()
{
	return this->velocity;
}

float Entity::GetVelocityX()
{
	return this->velocity.x;
}

void Entity::SetVelocityX(float x)
{
	this->velocity.x = x;
}

void Entity::AddVelocityX(float dx)
{
	this->velocity.x += dx;
}

float Entity::GetVelocityY()
{
	return this->velocity.y;
}

void Entity::SetVelocityY(float y)
{
	this->velocity.y = y;
}

void Entity::AddVelocityY(float dy)
{
	this->velocity.y += dy;
}

void Entity::SetIsOnAir(float IsOnAir)
{
	this->IsOnAir = IsOnAir;
}

bool Entity::GetIsOnAir()
{
	return this->IsOnAir;
}


void Entity::SetMoveDirection(Entity_Direction _direction)
{
	this->direction = _direction;
}

Entity::Entity_Direction Entity::GetMoveDirection()
{
	return this->direction;
}

void Entity::Update(float dt)
{
	this->position.x += this->velocity.x*dt;
	this->position.y += this->velocity.y*dt;

}
