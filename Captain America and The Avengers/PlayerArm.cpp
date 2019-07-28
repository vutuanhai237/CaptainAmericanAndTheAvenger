#include "PlayerArm.h"
#include "Player.h"

PlayerArm::PlayerArm()
{
	Player *player = Player::GetInstance();
	Entity::position = player->GetPosition();
	Entity::size.cx = PLAYER_ARM_SIZE_WIDTH;
	Entity::size.cy = PLAYER_ARM_SIZE_HEIGHT;
	if (player->GetMoveDirection() == Entity::Entity_Direction::LeftToRight)
		Entity::position.x += 19.5f;
	else
		Entity::position.x -= 19.5f;
	if (player->GetCurrentState() == PlayerState::NameState::ducking_punching)
		Entity::position.y -= 2;
	else
		Entity::position.y += 11;

	Entity::SetType(Entity::Entity_Type::player_weapon_type);
	Entity::SetTag(Entity::Entity_Tag::none);

	IsPunchComplete = false;
}

int PlayerArm::OnCollision(Entity *obj, float dt)
{
	if (!IsPunchComplete)
		return 0;
	else
		return 1;
}

void PlayerArm::Update(float dt)
{
	IsPunchComplete = true;
}

PlayerArm::~PlayerArm()
{
}