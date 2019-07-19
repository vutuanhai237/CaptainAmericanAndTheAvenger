#include "ShieldState.h"

ShieldState::ShieldState()
{
	CurrentState = NameState::Nomal;
}

ShieldState::ShieldState(NameState State)
{
	CurrentState = State;
}

void ShieldState::SetCurrentState(NameState State)
{
	CurrentState = State;
}

ShieldState::NameState ShieldState::GetCurrentState()
{
	return CurrentState;
}
