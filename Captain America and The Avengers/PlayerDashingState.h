#pragma once
#include "PlayerState.h"
#include "Player.h"
class PlayerDashingState : public PlayerState
{
public:
	PlayerDashingState();
	~PlayerDashingState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;

	virtual void HandleInput(float dt);
	bool IsDucking;
	bool IsGong;
};

