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

void Entity::SetPosition(D3DXVECTOR2 position)
{
	this->position = position;
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

void Entity::SetPositionX(float x)
{
	this->position.x = x;
}

void Entity::SetPositionY(float y)
{
	this->position.y = y;
}


void Entity::SetMoveDirection(Entity_Direction _direction)
{
	this->direction = _direction;
}

Entity::Entity_Direction Entity::GetMoveDirection()
{
	return this->direction;
}

void Entity::SetJumpDirection(Entity_Jump_Direction _jump_direction)
{
	this->jump_direction = _jump_direction;
}

Entity::Entity_Jump_Direction Entity::GetJumpDirection()
{
	return this->jump_direction;
}

void Entity::Update(float dt)
{

	if (this->direction == Entity::Entity_Direction::LeftToRight) {
		this->velocity.x = fabs(this->GetVelocityX());
	}
	else {
		this->velocity.x = -fabs(this->GetVelocityX());
	}
	if (this->jump_direction == Entity::Entity_Jump_Direction::BotToTop) {
		this->velocity.y = fabs(this->GetVelocityY());
	}
	else {
		this->velocity.y = -fabs(this->GetVelocityY());
	}
	this->position.x += this->velocity.x*dt;
	this->position.y += this->velocity.y*dt;

}

void Entity::SetBoudingBox(const BoundingBox &box)
{
	this->box = box;
}

void Entity::SetBoudingBox(int width, int height)
{
	SIZE size;
	size.cx = width;
	size.cy = height;
	this->SetBoudingBox(BoundingBox(size));
}
