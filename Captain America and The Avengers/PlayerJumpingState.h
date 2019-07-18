#pragma once
#include "PlayerState.h"
#include "PlayerJumpingDownState.h"
#include "PlayerKickingState.h"
#include "Player.h"
class PlayerJumpingState: public PlayerState
{
public:
	float time_air;
	PlayerJumpingState();
	~PlayerJumpingState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Render();
	virtual void HandleInput(float dt);
};

