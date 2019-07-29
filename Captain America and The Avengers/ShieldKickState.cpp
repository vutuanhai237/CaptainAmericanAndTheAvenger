#include "ShieldKickState.h"
#include "Player.h"
#include "Shield.h"

ShieldKickState::ShieldKickState()
{
	this->SetCurrentState(NameState::Nomal);
	Shield::GetInstance()->GetAnimation()->SetFrame(1);
}

int ShieldKickState::GetDamage()
{
	return 0;
}

void ShieldKickState::Update(float dt)
{
	VirtualPoint = Player::GetInstance()->GetPosition();
	if (Player::GetInstance()->GetMoveDirection() == Entity::Entity_Direction::LeftToRight)
		VirtualPoint.x += SHIELD_NOMAL_KICKING_DELTA_X;
	else
		VirtualPoint.x -= SHIELD_NOMAL_KICKING_DELTA_X;
	VirtualPoint.y += SHIELD_NOMAL_KICKING_DELTA_Y;
}

void ShieldKickState::Draw()
{
	if (Player::GetInstance()->GetMoveDirection() == Entity::Entity_Direction::LeftToRight)
		Shield::GetInstance()->GetAnimation()->SetScale(1, 1);
	else
		Shield::GetInstance()->GetAnimation()->SetScale(-1, 1);
	Shield::GetInstance()->GetAnimation()->Draw(VirtualPoint);
}