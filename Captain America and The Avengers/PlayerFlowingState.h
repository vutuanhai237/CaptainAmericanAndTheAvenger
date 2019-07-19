#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerJumpingState.h"
#include "PlayerIdleState.h"
#include "Framework//DirectInput.h"
class PlayerFlowingState : public PlayerState
{
public:
	PlayerFlowingState();
	~PlayerFlowingState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Render();
	virtual void HandleInput(float dt);
	bool IsPunching;
};

