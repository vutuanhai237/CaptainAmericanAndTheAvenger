#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerIdleState.h"

class PlayerShockingState : public PlayerState
{
public:
	float time_shocking;
	int damage;
	PlayerShockingState(int damage);
	~PlayerShockingState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;

	virtual void HandleInput(float dt);
};

