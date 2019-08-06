#include "PlayerLeg.h"
#include "Player.h"

PlayerLeg::PlayerLeg()
{
	Player *player = Player::GetInstance();
	Entity::position = player->GetPosition();
	Entity::size.cx = PLAYER_LEG_SIZE_WIDTH;
	Entity::size.cy = PLAYER_LEG_SIZE_HEIGHT;
	if (player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight)
	{
		Entity::position.x += 24;
	}
	else
	{
		Entity::position.x -= 24;
	}
	Entity::position.y += 2;
	Entity::SetType(Entity::Entity_Type::player_weapon_type);
	Entity::SetTag(Entity::Entity_Tag::none);
	IsKickComplete = false;
}

int PlayerLeg::OnCollision(Entity *obj, float dt)
{
	if (!IsKickComplete)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void PlayerLeg::Update(float dt)
{
	IsKickComplete = true;
}

PlayerLeg::~PlayerLeg()
{
	Entity::~Entity();
}
