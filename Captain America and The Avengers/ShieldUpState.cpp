#include "ShieldUpState.h"
#include "Shield.h"
#include "Player.h"

ShieldUpState::ShieldUpState()
{
	this->SetCurrentState(NameState::ShieldUp);
	Shield::GetInstance()->GetAnimation()->SetFrame(3);
}

void ShieldUpState::Update(float dt)
{
	Player *player = Player::GetInstance();
	VirtualPoint = player->GetPosition();
	int direction = player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight ? 1 : -1;
	VirtualPoint.x += SHIELD_UP_DELTA_X * direction;
	VirtualPoint.y += SHIELD_UP_DELTA_Y;
}

void ShieldUpState::Draw()
{
	Shield::GetInstance()->GetAnimation()->Draw(VirtualPoint);
}
