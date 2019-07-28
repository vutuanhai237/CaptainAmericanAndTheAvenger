#pragma once
#include "Framework//Animation.h"
#include "Framework//DirectInput.h"
#include "DataCollect.h"
#include "Entity.h"
#include <math.h>
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
		beaten
	};
	BossWizardState();
	~BossWizardState();
	BossWizardState(BossWizardState::NameState current_state);
	virtual void Update(float dt) = 0;
	virtual BoundingBox GetBoundingBox() = 0;
	virtual void Draw() = 0;
	virtual void HandleInput(float dt) = 0;
	BossWizardState::NameState GetCurrentState();
	void SetCurrentState(BossWizardState::NameState current_state);

protected:
	BossWizardState::NameState current_state;
	bool IsDucking;
	bool IsDucking_Punching;
	bool IsThrowing;
	bool IsPunching;
	bool IsRolling;

};

