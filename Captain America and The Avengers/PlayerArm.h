#pragma once
#include "Entity.h"

#define PLAYER_ARM_SIZE_WIDTH 11
#define PLAYER_ARM_SIZE_HEIGHT 4

class PlayerArm : public Entity
{
public:
	PlayerArm();
	int OnCollision(Entity *, float dt) override;
	void Update(float dt) override;
	~PlayerArm(); 
private:
	bool IsPunchComplete;
};

