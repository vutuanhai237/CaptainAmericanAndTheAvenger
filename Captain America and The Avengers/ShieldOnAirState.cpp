#include "ShieldOnAirState.h"
#include "Shield.h"
#include "Player.h"
#include "Framework//Debug.h"
ShieldOnAirState::ShieldOnAirState()
{
	SetCurrentState(NameState::OnAir);
	Shield::GetInstance()->GetAnimation()->SetFrame(2);
}

void ShieldOnAirState::Update(float dt)
{
	Player *player = Player::GetInstance();

	if (player->GetCurrentState() == PlayerState::NameState::ducking_punching) {
		if (player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
			VirtualPoint.x = player->GetPosition().x + SHIELD_ON_AIR_DUCKING_PUNCHING_DELTA_X;

		}
		else {
			VirtualPoint.x = player->GetPosition().x - SHIELD_ON_AIR_DUCKING_PUNCHING_DELTA_X;

		}
		VirtualPoint.y = player->GetPosition().y + SHIELD_ON_AIR_DUCKING_PUNCHING_DELTA_Y;
		return;
	}

	VirtualPoint.y = player->GetPosition().y + SHIELD_ON_AIR_DELTA_Y;
	if (player->GetJumpDirection() == Entity::Entity_Jump_Direction::BotToTop)
		VirtualPoint.y += 5;
	if (player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight)
		VirtualPoint.x = player->GetPosition().x + SHIELD_ON_AIR_DELTA_X;
	else
		VirtualPoint.x = player->GetPosition().x - SHIELD_ON_AIR_DELTA_X;
	
}

void ShieldOnAirState::Draw()
{
	
	Player *player = Player::GetInstance();
	if (player->OnTheWater) {
		return;
	}
	if (!Player::GetInstance()->IsRolling)
		Shield::GetInstance()->GetAnimation()->Draw(VirtualPoint);
}
