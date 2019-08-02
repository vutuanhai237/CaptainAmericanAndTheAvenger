#pragma once
#include "Framework//Animation.h"
#include "Framework//DirectInput.h"
#include "DataCollect.h"
#include "Entity.h"
#include <math.h>
#define UP_KEY DIK_UPARROW
#define DOWN_KEY DIK_DOWNARROW
#define LEFT_KEY DIK_LEFTARROW
#define RIGHT_KEY DIK_RIGHTARROW
#define ATTACK_KEY DIK_Z
#define JUMP_KEY DIK_X

class PlayerState
{
public:
	
	enum NameState {
		idle,
		running,
		jumping,
		throwing,
		dashing,
		beaten,
		shield_up,
		ducking,
		ducking_punching,
		rolling,
		die,
		diving,
		flowing,
		hang_on,
		jumping_down,
		jump_from_rope,
		kicking,
		punching,
		shield_down,
		shocking
	};
	PlayerState();
	PlayerState(PlayerState::NameState current_state);
	~PlayerState();
	virtual void Update(float dt) = 0;
	virtual BoundingBox GetBoundingBox() = 0;
	virtual void Draw() = 0;
	virtual void HandleInput(float dt) = 0;
	PlayerState::NameState GetCurrentState();
	void SetCurrentState(PlayerState::NameState current_state);

protected:
	PlayerState::NameState current_state;
	bool IsDucking;
	bool IsDucking_Punching;
	bool IsThrowing;
	bool IsPunching;
	bool IsRolling;
};

