#include "ShieldDownState.h"
#include "Player.h"
#include "Shield.h"

ShieldDownState::ShieldDownState()
{
	this->SetCurrentState(NameState::ShieldDown);
	Shield::GetInstance()->GetAnimation()->SetFrame(4);
}

void ShieldDownState::Update(float dt)
{
	VirtualPoint = Player::GetInstance()->GetPosition();
	VirtualPoint.x += SHIELD_DOWN_DELTA_X;
	VirtualPoint.y += SHIELD_DOWN_DELTA_Y;
}

void ShieldDownState::Draw()
{
	Shield::GetInstance()->GetAnimation()->Draw(VirtualPoint);
}
