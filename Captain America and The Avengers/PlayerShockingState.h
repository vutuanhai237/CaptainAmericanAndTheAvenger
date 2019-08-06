#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerIdleState.h"

class PlayerShockingState : public PlayerState
{
public:
	int damage;
	float time_shocking;
	PlayerShockingState(int damage);
	~PlayerShockingState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

