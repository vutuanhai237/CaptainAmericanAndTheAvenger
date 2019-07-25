#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "PlayerIdleState.h"

class PlayerBeatenState : public PlayerState
{
public:
	float time_beaten;
	PlayerBeatenState();
	~PlayerBeatenState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;

	virtual void HandleInput(float dt);
};

