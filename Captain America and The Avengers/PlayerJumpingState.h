#pragma once
#include "PlayerState.h"
#include "PlayerJumpingDownState.h"
#include "PlayerKickingState.h"
#include "Player.h"
class PlayerJumpingState: public PlayerState
{
public:
	PlayerJumpingState();
	~PlayerJumpingState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

