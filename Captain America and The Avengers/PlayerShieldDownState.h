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
	float time_nhuns;
	bool IsNhunsLen;
	PlayerShieldDownState();
	~PlayerShieldDownState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

