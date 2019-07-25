#include "Shield.h"
#include "ShieldNomalState.h"
#include "Player.h"
#include "PlayerState.h"

ShieldNomalState::ShieldNomalState()
{
	this->SetCurrentState(NameState::Nomal);
	Shield::GetInstance()->GetAnimation()->SetFrame(1);
}

void ShieldNomalState::Update(float dt)
{
	Player *player = Player::GetInstance();
	VirtualPoint = player->GetPosition();
	int direction = player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight ? 1 : -1;
	switch (player->GetCurrentAnimation()->GetName())
	{
	case PlayerState::NameState::idle:
	case PlayerState::NameState::running:
		VirtualPoint.x += SHIELD_NOMAL_DELTA_X * direction;
		VirtualPoint.y += SHIELD_NOMAL_DELTA_Y - (player->GetCurrentAnimation()->GetNumberCurrentFrame() % 2);
		break;
	case PlayerState::NameState::ducking:
		VirtualPoint.x += SHIELD_NOMAL_DUCKING_DELTA_X * direction;
		VirtualPoint.y += SHIELD_NOMAL_DUCKING_DELTA_Y;
		break;
	case PlayerState::NameState::dashing:
		switch (player->GetCurrentAnimation()->GetNumberCurrentFrame())
		{
		case 1:
			VirtualPoint.x += SHIELD_NOMAL_DUCKING_DELTA_X * direction;
			VirtualPoint.y += SHIELD_NOMAL_DUCKING_DELTA_Y;
			break;
		case 2:
			VirtualPoint.x += SHIELD_NOMAL_DASHING_FRAME_2_DELTA_X * direction;
			VirtualPoint.y += SHIELD_NOMAL_DASHING_FRAME_2_DELTA_Y;
			break;
		case 3:
			VirtualPoint.x += SHIELD_NOMAL_DASHING_FRAME_3_DELTA_X * direction;
			VirtualPoint.y += SHIELD_NOMAL_DASHING_FRAME_3_DELTA_Y;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void ShieldNomalState::Draw()
{
	if (Player::GetInstance()->OnTheWater) {
		return;
	}
	Shield::GetInstance()->GetAnimation()->Draw(VirtualPoint);
}
