#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerJumpingState.h"
#include "PlayerIdleState.h"
#include "PlayerState.h"
#include "Framework//DirectInput.h"

class PlayerShieldUpState : public PlayerState
{
public:
	PlayerShieldUpState();
	~PlayerShieldUpState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void HandleInput(float dt);
};

