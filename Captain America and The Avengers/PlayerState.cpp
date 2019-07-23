#include "PlayerState.h"
#include "Player.h"

PlayerState::PlayerState()
{
	this->current_state = PlayerState::idle;
}

PlayerState::PlayerState(PlayerState::NameState current_state)
{
	this->current_state = current_state;
}

PlayerState::~PlayerState()
{
}

PlayerState::NameState PlayerState::GetCurrentState()
{
	return this->current_state;
}

void PlayerState::SetCurrentState(PlayerState::NameState current_state)
{
	this->current_state = current_state;
}


