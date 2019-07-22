#include "Collision.h"
#include <iostream>
using namespace std;

Collision* Collision::instance = NULL;


Collision* Collision::getInstance()
{
	if (!instance)
		instance = new Collision();
	return instance;
}

CollisionOut Collision::SweptAABB(BoundingBox recta, BoundingBox rectb)
{
	CollisionOut out;
	if (IsCollide(recta, rectb))
	{
		out.CollisionTime = 0.0f;
		if (recta.left <= rectb.left)
		{
			out.side = CollisionSide::right;
			return out;
		}
		if (recta.right >= rectb.right)
		{
			out.side = CollisionSide::left;
			return out;
		}
		if (recta.top >= rectb.top)
		{
			out.side = CollisionSide::bottom;
			return out;
		}
		if (recta.bottom <= rectb.bottom)
		{
			out.side = CollisionSide::top;
			return out;
		}
	}

	out.CollisionTime = 2;
	out.side = CollisionSide::none;
	recta.vx = recta.vx - rectb.vx;
	recta.vy = recta.vy - rectb.vy;

	BoundingBox test;
	test.top = recta.vy > 0 ? recta.top + recta.vy : recta.top;
	test.bottom = recta.vy > 0 ? recta.bottom : recta.bottom + recta.vy;
	test.left = recta.vx > 0 ? recta.left : recta.left + recta.vx;
	test.right = recta.vx > 0 ? recta.right + recta.vx : recta.right;
	if (!IsCollide(test, rectb))
	{
		return out;
	}
	if (recta.vx > 0.0f)
	{
		dxEntry = rectb.left - recta.right;
		dxExit = rectb.right - recta.left;
	}
	else
	{
		dxEntry = rectb.right - recta.left;
		dxExit = rectb.left - recta.right;

	}
	if (recta.vy > 0.0f)
	{
		dyEntry = rectb.bottom - recta.top;
		dyExit = rectb.top - recta.bottom;
	}
	else
	{
		dyEntry = rectb.top - recta.bottom;
		dyExit = rectb.bottom - recta.top;

	}


	if (recta.vx == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / recta.vx;
		txExit = dxExit / recta.vx;
	}
	if (recta.vy == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / recta.vy;
		tyExit = dyExit / recta.vy;
	}

	float entryTime = max(txEntry, tyEntry);
	float exitTime = min(tyExit, txExit);
	if (entryTime > exitTime || (txEntry < 0.0f&&tyEntry < 0.0f) || txEntry > 1.0f || tyEntry > 1.0f)
		return out;
	out.CollisionTime = entryTime;
	if (txEntry > tyEntry)
	{
		if (dxEntry < 0)
			out.side = CollisionSide::left;
		else
		{
			out.side = CollisionSide::right;
		}
	}
	else
	{
		if (dyEntry < 0)
			out.side = CollisionSide::bottom;
		else
		{
			out.side = CollisionSide::top;
		}
	}
	return out;
}

bool Collision::IsCollide(BoundingBox box1, BoundingBox box2)
{
	return !(box1.left > box2.right || box1.right < box2.left || box1.top < box2.bottom || box1.bottom > box2.top);
}