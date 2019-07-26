#include "BlueSoldier.h"
#include "Shield.h"
#include "FrameWork//Debug.h"
void BlueSoldier::Update(float dt)
{


}

void BlueSoldier::UpdateStupidLevel(float dt)
{
	
}

void BlueSoldier::UpdateNormalLevel(float dt)
{

}

void BlueSoldier::UpdateCleverLevel(float dt)
{


}

int BlueSoldier::OnCollision(Entity* obj, float dt)
{
	return Enemy::OnCollision(obj, dt);
}

void BlueSoldier::Draw()
{

	Enemy::Draw();
}

BoundingBox BlueSoldier::GetBoundingBox()
{
	return Enemy::GetBoundingBox();
}

bool BlueSoldier::IsCollisionWithGround(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = BLUE_SOLDIER_SIZE_WIDTH;
	FootSize.cy = BLUE_SOLDIER_FOOT_HEIGHT;
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
				position.y = item->GetPosition().y + BLUE_SOLDIER_SIZE_HEIGHT / 2;
				return true;
			}
		}
	}
	return false;
}

BlueSoldier::BlueSoldier(int level, D3DXVECTOR2 position_spawn, D3DXVECTOR2 position_goto, bool IsCrossed)
{
}

BlueSoldier::~BlueSoldier()
{
}

