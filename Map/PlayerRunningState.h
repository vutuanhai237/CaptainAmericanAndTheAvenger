#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerRunningState: public PlayerState
{
public:
	PlayerRunningState();
	~PlayerRunningState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Render();
	virtual void HandleInput();
};

