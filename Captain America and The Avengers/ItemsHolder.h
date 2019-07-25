#pragma once
#include <vector>
#include "Entity.h"
#include "Framework/Animation.h"

#define ITEMS_HOLDER_SIZE_WIDTH 16
#define ITEMS_HOLDER_SIZE_HEIGHT 16

class ItemsHolder : public Entity
{
public:
	ItemsHolder(float x, float y);
	~ItemsHolder();

	BoundingBox GetBoundingBox() override;
	int OnCollision(Entity *, float dt) override;
	void Update(float dt) override;
	void Draw() override;
	void PutOnItem(int Item_Tag);

	static int AnimationID;
	static int ID_1up;
	static int ID_5Point;
	static int ID_ExitOrb;
	static int ID_FullHeal;
	static int ID_HalfHeal;
	static int ID_HighPoint;
	static int ID_SmallGem;
	static int ID_LargeGem;
private:
	Animation *animation;
	BoundingBox HitBox;
	std::vector<Entity*> *Items;
};