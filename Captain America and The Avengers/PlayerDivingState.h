#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerJumpingState.h"
#include "PlayerDuckingPunchingState.h"
#include "PlayerIdleState.h"
#include "Framework//DirectInput.h"
class PlayerDivingState : public PlayerState
{
public:
	PlayerDivingState();
	~PlayerDivingState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void HandleInput(float dt);
	
};

