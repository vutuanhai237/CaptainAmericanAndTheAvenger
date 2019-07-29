#include "OnOffSwitch.h"
#include "SceneManager.h"
#include "Shield.h"

OnOffSwitch::OnOffSwitch(int x, int y) : Entity()
{
	Entity::tag = Entity::Entity_Tag::on_off_switch;
	Entity::type = Entity::Entity_Type::static_type;

	Entity::size.cx = 16;
	Entity::size.cy = 16;
	Entity::position.x = x;
	Entity::position.y = y;

	InvincibleTimeCounter = -0.0f;
}

int OnOffSwitch::OnCollision(Entity *obj, float dt)
{
	if (InvincibleTimeCounter > 0)
		return 0;
	if (obj->GetType() != Entity::Entity_Type::player_weapon_type)
		return 0;
	if (obj->GetTag() == Entity::Entity_Tag::shield)
		if (Shield::GetInstance()->GetShieldState()->GetCurrentState() != ShieldState::ShieldAttack)
			return 0;

	if (Collision::getInstance()->IsCollide(Entity::GetBoundingBox(), obj->GetBoundingBox()))
	{
		SceneManager::GetInstance()->GetCurrentScene()->SwapMap();
		InvincibleTimeCounter = ON_OFF_SWITCH_TIME_BETWEEN_ATTACK;
	}
}

void OnOffSwitch::Update(float dt)
{
	InvincibleTimeCounter -= dt;
}
