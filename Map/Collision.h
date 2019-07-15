#pragma once
#include "Entity.h"

class Collision
{
public:
	Collision();
	~Collision();
	// Lấy box collider tại vị trí sẽ va chạm
	//static BoxCollider GetBoardPhasing(BoxCollider box1, D3DXVECTOR2 velocity);

	//static Entity::CollsionResult RectvsRect(BoxCollider rec1, BoxCollider rec2); // Kiểm tra 2 rectangle với nhau
	//static bool IsCollide(BoxCollider rec1, BoxCollider rec2, D3DXVECTOR2 vel = D3DXVECTOR2(0,0));

	// Kiểm tra vị trí va chạm
	//static float SweptAABB(BoxCollider rec1, BoxCollider rec2, D3DXVECTOR2 vel1, D3DXVECTOR2 vel2, Entity::Side_Collision &side, float dt = 1 / 60);
	//static float SweptAABB(Entity* entity1, Entity* entity2, Entity::Side_Collision &side, float dt = 1 / 60);
};

