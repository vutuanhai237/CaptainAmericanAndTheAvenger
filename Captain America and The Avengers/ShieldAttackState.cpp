#include "ShieldAttackState.h"
#include "Player.h"
#include "Shield.h"

#include <list>

ShieldAttackState::ShieldAttackState()
{
	this->SetCurrentState(NameState::ShieldAttack);
	Player *player = Player::GetInstance();
	direction = player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight ? 1 : -1;
	VirtualPoint = player->GetPosition();
	VirtualPoint.x += SHIELD_BEFORE_ATTACK_FRAME_1_DELTA_X * direction;
	VirtualPoint.y += SHIELD_BEFORE_ATTACK_FRAME_1_DELTA_Y;
	FrameLock = 1;
	delta = 0.0f;
	IsComeBack = false;
	DeltaSlow = SHIELD_ATTACK_VELOCITY;
}

void ShieldAttackState::Update(float dt)
{

	delta += dt;

	Player *player = Player::GetInstance();
	Shield *shield = Shield::GetInstance();

	if (player->GetCurrentAnimation()->GetName() == PlayerState::NameState::throwing) {
		if (this->FrameLock < 2)
		{

			FrameLock = player->GetCurrentAnimation()->GetNumberCurrentFrame();
			if (FrameLock == 2)
			{
				VirtualPoint = player->GetPosition();
				VirtualPoint.x += SHIELD_BEFORE_ATTACK_FRAME_2_DELTA_X * direction;
				VirtualPoint.y += SHIELD_BEFORE_ATTACK_FRAME_2_DELTA_Y;
				this->FrameLock++;
			}
			return;
		}
	}
	else {
		this->FrameLock = 2;
	}
	
	
	if (delta >= SHIELD_ATTACK_TIME_OUT && !IsComeBack)
	{
		DeltaSlow -= SHIELD_ATTACK_ACCELERATION;
		if (DeltaSlow <= 0)
		{
			direction *= -1;
			IsComeBack = true;
		}
		VirtualPoint.x += DeltaSlow * direction;
		return;
	}
	
	if (IsComeBack)
	{
		float deltaY = player->GetPosition().y - VirtualPoint.y;
		if (abs(deltaY) > SHIELD_FOLLOW_VELOCITY_Y)
			deltaY = deltaY > 0 ? SHIELD_FOLLOW_VELOCITY_Y : -SHIELD_FOLLOW_VELOCITY_Y;

		VirtualPoint.y += deltaY;
	}
	VirtualPoint.x += SHIELD_ATTACK_VELOCITY * direction;

	if (IsComeBack && abs(VirtualPoint.x - player->GetPosition().x) <= PLAYER_SIZE_WIDTH)
	{
		this->SetCurrentState(NameState::Nomal);
		ShieldState *buffer = shield->GetBufferState();
		shield->SetShieldState(buffer);
		switch (buffer->GetCurrentState())
		{
		case ShieldState::NameState::Nomal:
		case ShieldState::NameState::ShieldKick:
			shield->GetAnimation()->SetFrame(1);
			break;
		case ShieldState::NameState::OnAir:
			shield->GetAnimation()->SetFrame(2);
			break;
		case ShieldState::NameState::ShieldUp:
			shield->GetAnimation()->SetFrame(3);
			break;
		case ShieldState::NameState::ShieldDown:
			shield->GetAnimation()->SetFrame(4);
			break;
		default:
			break;
		}
	}
}

void ShieldAttackState::Draw()
{
	Shield::GetInstance()->GetAnimation()->SetFrame(3);
	Shield::GetInstance()->GetAnimation()->Draw(VirtualPoint);	
}

BoundingBox ShieldAttackState::GetBoundingBox()
{
	SIZE size;
	if (Player::GetInstance()->GetCurrentState() == PlayerState::NameState::throwing)
	{
		size.cx = -0;
		size.cy = -0;
	}
	else
	{
		size.cx = 16;
		size.cy = 9;
	}
	return BoundingBox(VirtualPoint, size, 0, 0);
}

