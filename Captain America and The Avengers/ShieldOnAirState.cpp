#include "ShieldOnAirState.h"
#include "Shield.h"
#include "Player.h"

ShieldOnAirState::ShieldOnAirState()
{
	SetCurrentState(NameState::OnAir);
	Shield::GetInstance()->GetAnimation()->SetFrame(2);
}

void ShieldOnAirState::Update(float dt)
{
	Player *player = Player::GetInstance();
	D3DXVECTOR2 PlayerLocation = Player::GetInstance()->GetPosition();
	VirtualPoint.y = player->GetPosition().y + SHIELD_ON_AIR_DELTA_Y;
	if (player->GetVelocityY() > 0)
		VirtualPoint.y += 3;
	if (player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight)
		VirtualPoint.x = player->GetPosition().x + SHIELD_ON_AIR_DELTA_X;
	else
		VirtualPoint.x = player->GetPosition().x - SHIELD_ON_AIR_DELTA_X;
}

void ShieldOnAirState::Draw()
{
	Player *player = Player::GetInstance();
	if (!Player::GetInstance()->IsRolling)
		Shield::GetInstance()->GetAnimation()->Draw(VirtualPoint);
}
