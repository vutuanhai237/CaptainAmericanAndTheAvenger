#pragma once
#include "Framework//Animation.h"
#include "Framework//DirectInput.h"

#include "Entity.h"
#include <math.h>
class PlayerState
{
public:
	enum NameState {
		idle,
		running,
		jumping,
		throwing,
		dashing,
		beaten
	};
	PlayerState();
	PlayerState(PlayerState::NameState current_state);
	~PlayerState();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Render();
	virtual void HandleInput();
	PlayerState::NameState GetCurrentState();
	void SetCurrentState(PlayerState::NameState current_state);

protected:
	PlayerState::NameState current_state;
};

