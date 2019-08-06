#pragma once
#include "PlayerState.h"
#include "Player.h"

class PlayerJumpingDownState : public PlayerState
{
public:
	float time_animation_before_flowing;
	bool IsDuocChuyenState;
	bool IsDuocChuyenAnimation;
	PlayerJumpingDownState();
	~PlayerJumpingDownState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
	Animation*animation_before_flowing;
};

