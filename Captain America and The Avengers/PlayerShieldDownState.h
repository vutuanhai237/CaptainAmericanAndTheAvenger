#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerRollingState.h"
#include "PlayerJumpingDownState.h"
#include "PlayerIdleState.h"
#include "PlayerState.h"
#include "Framework//DirectInput.h"
class PlayerShieldDownState : public PlayerState
{
public:
	int i = 0;
	PlayerShieldDownState();
	~PlayerShieldDownState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Render();
	virtual void HandleInput(float dt);
};

