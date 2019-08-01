#include "ShieldDownState.h"
#include "Player.h"
#include "Shield.h"

ShieldDownState::ShieldDownState()
{
	this->SetCurrentState(NameState::ShieldDown);
	Shield::GetInstance()->GetAnimation()->SetFrame(4);
}

int ShieldDownState::GetDamage()
{
	if (Player::GetInstance()->time_invisible > 0) {
		return 0;
	}
	return SHIELD_DOWN_DAMAGE;
}

void ShieldDownState::Update(float dt)
{
	VirtualPoint = Player::GetInstance()->GetPosition();
	VirtualPoint.x += SHIELD_DOWN_DELTA_X;
	VirtualPoint.y += SHIELD_DOWN_DELTA_Y;
}

void ShieldDownState::Draw()
{
	if (Player::GetInstance()->GetCurrentState() == PlayerState::NameState::beaten) {
		return;
	}
	Shield::GetInstance()->GetAnimation()->Draw(VirtualPoint);
}

BoundingBox ShieldDownState::GetBoundingBox()
{
	SIZE size;
	size.cx = 24;
	size.cy = 6;
	return BoundingBox(VirtualPoint, size, 0, 0);
}
