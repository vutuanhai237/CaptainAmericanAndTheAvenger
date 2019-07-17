#include "Collision.h"
#include<iostream>
using namespace std;

Collision* Collision::instance = NULL;


Collision* Collision::getInstance()
{
	if (!instance)
		instance = new Collision();
	return instance;
}

collisionOut Collision::SweptAABB(BoundingBox recta, BoundingBox rectb)
{
	collisionOut out;
	out.collisionTime = 2;
	out.side = CollisionSide::none;
	//recta.vx = rectb.vx - recta.vx;
	//recta.vy = rectb.vy - recta.vy;
	if (!IsCollide(recta, rectb))
	{
		int a = 1;
		return out;
	}
	if (recta.vx > 0.0f)
	{
		dxEntry = rectb.left - recta.right;
		dxExit = rectb.right - recta.left;
	}
	else
	{
		/*dxEntry = rectb.right - recta.left;
		dxExit = rectb.left - recta.right;*/
		dxEntry = recta.left - rectb.right;
		dxExit = recta.right - rectb.left;
	}
	if (recta.vy > 0.0f)
	{
		dyEntry = rectb.bottom - recta.top;
		dyExit = rectb.top - recta.bottom;
	}
	else
	{
		/*dyEntry = rectb.bottom - recta.top;
		dyExit = rectb.top - recta.bottom;*/
		dyEntry = recta.bottom - rectb.top;
		dyExit = recta.top - rectb.bottom;
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
	out.collisionTime = entryTime;
	
	if (txEntry < tyEntry)
	{
		if (dyEntry > 0.0f)
		{
			out.side = CollisionSide::top;
		}
		else
		{
			out.side = CollisionSide::bottom;
		}

	}
	else
	{
		if (dxEntry > 0.0f)
		{
			out.side = CollisionSide::right;
		}
		else
		{
			out.side = CollisionSide::bottom;
		}
	}
	if (out.side == CollisionSide::bottom)
	{
		int a = 1;
	}
	return out;
}


bool Collision::IsCollide(BoundingBox box1, BoundingBox box2)
{
	return !(box1.left > box2.right || box1.right < box2.left || box1.top < box2.bottom || box1.bottom > box2.top);
}