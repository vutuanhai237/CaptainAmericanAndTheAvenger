#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerJumpingDownState : public PlayerState
{
public:
	float time_air;
	PlayerJumpingDownState();
	~PlayerJumpingDownState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Render();
	virtual void HandleInput(float dt);
	Animation*animation_before_flowing;
};

