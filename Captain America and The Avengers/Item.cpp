#include "Item.h"
#include "ItemsHolder.h"
#include "SceneManager.h"
#include "Player.h"

Item::Item(float x, float y, int tag)
{
	Entity::SetTag(Entity::Entity_Tag::item);
	Entity::SetType(Entity::Entity_Type::item_type);
	PriTag = tag;
	delta = 0;
	FrameCounter = 0;
	CanFalling = true;
	direction = 1;

	size.cx = 4;
	size.cy = 12;
	position.x = x;
	position.y = y;

	switch (tag)
	{
	case Item_Tag::ExitOrb:
		animation = new Animation(ItemsHolder::ID_ExitOrb, 2);
		Entity::SetTag(Entity::Entity_Tag::item_exit_orb);
		break;
	case Item_Tag::OneUp:
		animation = new Animation(ItemsHolder::ID_1up, 1);
		break;
	case Item_Tag::SmallGem:
		animation = new Animation(ItemsHolder::ID_SmallGem, 2);
		break;
	case Item_Tag::LargeGem:
		animation = new Animation(ItemsHolder::ID_LargeGem, 2);
		break;
	case Item_Tag::HalfHeal:
		animation = new Animation(ItemsHolder::ID_HalfHeal, 1);
		break;
	case Item_Tag::FullHeal:
		animation = new Animation(ItemsHolder::ID_FullHeal, 1);
		break;
	case Item_Tag::FivePoint:
		animation = new Animation(ItemsHolder::ID_5Point, 1);
		break;
	case Item_Tag::HighPoint:
		animation = new Animation(ItemsHolder::ID_HighPoint, 1);
		break;
	default:
		throw L"Sai tag!";
		break;
	}
	animation->SetTime(0.05f);
}


Item::~Item()
{
	delete animation;
}

BoundingBox Item::GetBoundingBox()
{
	return BoundingBox(D3DXVECTOR2(position.x, position.y + 4), size, 0, ITEM_VELOCITY_Y*direction);
}

void Item::Update(float dt)
{
	delta += dt;
	animation->Update(dt);	
	FrameCounter++;

	if (CanFalling)
	{
		if (direction > 0 && delta >= ITEM_TIME_REVERT)
			direction = -1;

		Entity::position.y += ITEM_VELOCITY_Y * direction;
		if (direction < 0)
			CheckFalling();
	}
}

int Item::OnCollision(Entity *obj, float dt)
{
	if (obj->GetTag() == Entity::Entity_Tag::player)
	{
		Player *player = Player::GetInstance();
		if (Collision::getInstance()->IsCollide(obj->GetBoundingBox(), GetBoundingBox()))
		{
			switch (PriTag)
			{
			case Item_Tag::ExitOrb:
				SceneManager::GetInstance()->GetCurrentScene()->IsExitAble = true;
				break;
			case Item_Tag::HalfHeal:
				Player::GetInstance()->hp += 4;
				break;
			case Item_Tag::FullHeal:
				player->hp += 8;
				if (player->hp > PLAYER_HP)
					player->hp = PLAYER_HP;
				break;
			default:
				break;
			}
			return 1;
		}
	}
	if (delta >= ITEM_LOOT_VANISHING)
	{
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->ItemCounter--;
		return 1;
	}
	return 0;
}

void Item::Draw()
{
	if (delta > ITEM_LOOT_WARNING)
		if (FrameCounter >> 2 & 1)
			return;
	animation->Draw(Entity::position);
}

void Item::CheckFalling()
{
	auto obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();
	for (Entity *item : obj)
		if (Collision::getInstance()->SweptAABB(item->GetBoundingBox(), GetBoundingBox()).CollisionTime <= 1.0)
		{
			Entity::position.y = item->GetPosition().y + (item->GetSize().cy + size.cy) / 2 - 4;
			CanFalling = false;
		}
}
