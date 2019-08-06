#pragma once
#include "Player.h"
#include "PlayerJumpingState.h"
#include "Framework//DirectInput.h"
class PlayerHangOnState : public PlayerState
{
public:
	PlayerHangOnState();
	~PlayerHangOnState();
	virtual void Update(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	virtual void HandleInput(float dt);
	bool IsJumpFromRope;
	float time_jump_form_rope;
	
};

