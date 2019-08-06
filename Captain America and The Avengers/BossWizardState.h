#pragma once
#include "Framework/Animation.h"
#include "Entity.h"

class BossWizardState
{
public:
	enum NameState {
		idle,
		running,
		flying,
		fire,
		punching,
		punching_fire,
		flying_fire,
		beaten,
		die
	};
	BossWizardState(BossWizardState::NameState current_state);
	BossWizardState();
	~BossWizardState();
	virtual void Update(float dt) = 0;
	virtual void Draw() = 0;
	virtual void HandleInput(float dt) = 0;
	// get
	virtual BoundingBox GetBoundingBox() = 0;
	BossWizardState::NameState GetCurrentState();
	// set
	void SetCurrentState(BossWizardState::NameState current_state);
protected:
	BossWizardState::NameState current_state;
	bool IsDucking;
	bool IsDucking_Punching;
	bool IsThrowing;
	bool IsPunching;
	bool IsRolling;
};