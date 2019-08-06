#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerIdleState.h"

class PlayerDieState : public PlayerState
{
public:
	float time_beaten;
	bool IsGuc;
	PlayerDieState();
	~PlayerDieState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
};

