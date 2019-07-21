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

bool Enemy::IsCollisionWithGround(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = PLAYER_SIZE_WIDTH;
	FootSize.cy = PLAYER_FOOT_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, velocity.x*dt, velocity.y*dt);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();

	if (foot.vy == 0)
	{
		for (auto item : obj)
		{
			if (item->GetTag() == Entity::Entity_Tag::ground && Checker->IsCollide(foot, BoundingBox(item->GetPosition(), item->GetSize(), 0, 0)))
				return true;
		}
		return false;
	}

	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		if (item->GetTag() == Entity::Entity_Tag::ground)
		{
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(foot, box2);
			if (tmp.side == CollisionSide::bottom)
			{
				position.y = item->GetPosition().y + PLAYER_SIZE_HEIGHT / 2;
				return true;
			}
		}
	}
	return false;
}