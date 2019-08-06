#include "BossWizardState.h"

BossWizardState::BossWizardState()
{
	this->current_state = BossWizardState::idle;
}

BossWizardState::BossWizardState(BossWizardState::NameState current_state)
{
	this->current_state = current_state;
}

BossWizardState::~BossWizardState()
{
}

BossWizardState::NameState BossWizardState::GetCurrentState()
{
	return this->current_state;
}

void BossWizardState::SetCurrentState(BossWizardState::NameState current_state)
{
	this->current_state = current_state;
}