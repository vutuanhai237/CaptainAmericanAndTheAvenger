#pragma once
#include<Windows.h>

enum CollisionSide {
	none,
	top,
	left,
	right,
	bottom
};

struct collisionOut {
	float collisionTime;
	CollisionSide side;
};

struct BoundingBox {
	float top, left, right, bottom;
	int vx, vy;
	SIZE size;
	BoundingBox(float top_, float left_, float bottom_, float right_, int vx_, int vy_)
	{
		top = top_;
		left = left_;
		bottom=bottom_;
		right = right_;
		vx = vx_;
		vy = vy_;
		size.cx = right_ - left_;
		size.cy = bottom_ - top_;
	}
	BoundingBox(SIZE _size)
	{
		size = _size;
		top = left = 0;
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
	static Collision * getInstance();
	collisionOut SweptAABB(BoundingBox recta, BoundingBox rectb);
	bool IsCollide(BoundingBox box1, BoundingBox box2);
};

