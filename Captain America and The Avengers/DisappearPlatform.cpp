#include "DisappearPlatform.h"

DisappearPlatform::DisappearPlatform(FLOAT WorldX, FLOAT WorldY) : Platform(WorldX, WorldY)
{
	Entity::tag = Entity::Entity_Tag::disappear_platform;
	Left = new Animation(Platform::DisappearPlatformID, 1);
	Left->Stop();
	Lpos = Entity::position;
	Lpos.x -= 8;
	Right = new Animation(Platform::DisappearPlatformID, 1);
	Right->Stop();
	Rpos = Entity::position;
	Rpos.x += 8;
	IsSplit = false;
	Started = false;
	Timer = DISAPPEAR_PLATFORM_TIME_FIRST_DISAPPEAR;
	FrameCounter = 0;
	MoveFlag = 0;
}

DisappearPlatform::~DisappearPlatform()
{
	delete Left;
	delete Right;
}

BoundingBox DisappearPlatform::GetBoundingBox()
{
	if (IsSplit)
	{
		SIZE size;
		size.cx = -0;
		size.cy = -0;
		return BoundingBox(Entity::position, size, 0, 0);
	}
	return Entity::GetBoundingBox();
}

int DisappearPlatform::OnCollision(Entity *obj, float dt)
{
	if (Started || obj->GetTag() != Entity::Entity_Tag::player)
	{
		return 0;
	}
	BoundingBox BoundingBoxPlayer = obj->GetBoundingBox();
	BoundingBoxPlayer.vx *= dt;
	BoundingBoxPlayer.vy *= dt;
	if (Collision::getInstance()->SweptAABB(BoundingBoxPlayer, this->GetBoundingBox()).side == CollisionSide::bottom)
	{
		Started = true;
	}
	return 0;
}

void DisappearPlatform::Update(float dt)
{
	if (!Started)
	{
		return;
	}
	Timer += dt;
	if (!IsSplit && Timer > DISAPPEAR_PLATFORM_TIME_SPLIT)
	{
		// Split
		IsSplit = true;
		Lpos.x -= 16;
		Rpos.x += 16;
		Timer -= DISAPPEAR_PLATFORM_TIME_SPLIT;
		MoveFlag = 2;
	}
	FrameCounter++;
	if (IsSplit && Timer > DISAPPEAR_PLATFORM_TIME_COMEBACK)
	{
		// Comeback
		if (MoveFlag == 0)
		{
			IsSplit = false;
			Timer = 0;
		}
		else if (FrameCounter % 16 == 0)
		{
			Lpos.x += 8;
			Rpos.x -= 8;
			MoveFlag--;
		}
	}
}

void DisappearPlatform::Draw()
{
	if (!IsSplit)
	{
		Left->Draw(Lpos);
		Right->Draw(Rpos);
	}
	else if (FrameCounter >> 1 & 1)
	{
		Left->Draw(Lpos);
		Right->Draw(Rpos); 
	}
}
