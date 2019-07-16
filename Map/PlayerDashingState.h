#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerDashingState : public PlayerState
{
public:
	PlayerDashingState();
	~PlayerDashingState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Render();
	virtual void HandleInput(float dt);
};

