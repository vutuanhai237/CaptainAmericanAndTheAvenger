#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerJumpingState: public PlayerState
{
public:
	PlayerJumpingState();
	~PlayerJumpingState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Render();
	virtual void HandleInput();
};

