#pragma once
#include <Windows.h>
#include <d3dx9.h>

enum CollisionSide 
{
	none,
	top,
	left,
	right,
	bottom
};

struct CollisionOut 
{
	float CollisionTime;
	CollisionSide side;
	CollisionOut() {
		CollisionTime = 2.0f;
		side = CollisionSide::none;
	}
};

struct BoundingBox // top > bottom
{
	float top, left, right, bottom;
	float vx, vy;
	BoundingBox(float top, float left, float bottom, float right, float vx, float vy) 
	{
		this->top = top;
		this->left = left;
		this->bottom = bottom;
		this->right = right;
		this->vx = vx;
		this->vy = vy;
	}
	BoundingBox(D3DXVECTOR2 position, SIZE size, float vx, float vy)
	{
		this->top = position.y + size.cy / 2.0f;
		this->bottom = top - size.cy;
		this->left = position.x - size.cx / 2.0f;
		this->right = left + size.cx;
		this->vx = vx;
		this->vy = vy;
	}
	BoundingBox() {};
	~BoundingBox() {};
};

class Collision
{
private:
	float dxEntry, dyEntry, dxExit, dyExit;
	float txEntry, tyEntry, txExit, tyExit;
	float entryTime, exitTime;

	static Collision *instance;
public:
	static Collision *getInstance();
	CollisionOut SweptAABB(BoundingBox recta, BoundingBox rectb);
	bool IsCollide(BoundingBox box1, BoundingBox box2);
};

