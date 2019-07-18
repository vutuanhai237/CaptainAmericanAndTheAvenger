#pragma once
#include "PlayerState.h"
#include "Player.h"
#define ROLLING_ACCELERATION 15.0f
class PlayerRollingState : public PlayerState
{
public:
	PlayerRollingState();
	~PlayerRollingState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Render();
	virtual void HandleInput(float dt);
	float time_air;
};

