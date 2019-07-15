#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerJumpingState.h"
#include "Framework//DirectInput.h"
class PlayerIdleState: public PlayerState
{
public:
	PlayerIdleState();
	~PlayerIdleState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Render();
	virtual void HandleInput();
};

