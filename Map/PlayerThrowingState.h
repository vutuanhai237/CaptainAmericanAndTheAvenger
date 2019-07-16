#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerJumpingState.h"
#include "PlayerDuckingState.h"
#include "PlayerIdleState.h"
#include "Framework//DirectInput.h"
class PlayerThrowingState : public PlayerState
{
public:
	PlayerThrowingState();
	~PlayerThrowingState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Render();
	virtual void HandleInput(float dt);
};

