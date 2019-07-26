#pragma once
#include "Entity.h"

#define PLAYER_LEG_SIZE_WIDTH 16
#define PLAYER_LEG_SIZE_HEIGHT 4

class PlayerLeg : public Entity
{
public:
	PlayerLeg();
	int OnCollision(Entity *, float dt) override;
	void Draw() override;
	~PlayerLeg();
private:
	bool IsKickComplete;
};

