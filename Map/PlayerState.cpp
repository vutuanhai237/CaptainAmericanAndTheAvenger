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

void PlayerState::Update(float dt)
{
	
}

void PlayerState::Draw()
{
}

void PlayerState::Render()
{
}

void PlayerState::HandleInput()
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


