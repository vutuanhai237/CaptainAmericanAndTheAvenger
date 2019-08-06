#pragma once
#include "Entity.h"
#include "Framework/Animation.h"

#define ITEM_TIME_REVERT 1/6.0f // frame
#define ITEM_LOOT_WARNING 3.0f
#define ITEM_LOOT_VANISHING 5.0f
#define ITEM_VELOCITY_Y 3.0f

class Item : public Entity
{
public:
	enum Item_Tag
	{
		ExitOrb,
		OneUp,
		SmallGem,
		LargeGem,
		HalfHeal,
		FullHeal,
		FivePoint,
		HighPoint
	};
	Item(float x, float y, int tag);
	~Item() override;
	BoundingBox GetBoundingBox() override;
	void Update(float dt) override;
	int OnCollision(Entity*, float dt) override;
	void Draw() override;
private:
	Animation *animation;
	float delta;
	int FrameCounter;
	bool CanFalling;
	int direction, PriTag;
	void CheckFalling();
};

