#include "Door.h"
#include "SceneManager.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "Shield.h"
#include "Framework/DirectInput.h"
#include "Framework/SoundManager.h"
int Door::IDDarkDoor = -1;
int Door::IDLightDoor = -1;

Door::Door(int WorldX, int WorldY, int GotoCode, int PositionGotoX, int PositionGotoY)
{
	Entity::tag = Entity::Entity_Tag::door;
	Entity::type = Entity::Entity_Type::static_type;
	Entity::position.x = WorldX;
	Entity::position.y = WorldY;
	Entity::size.cx = 32;
	Entity::size.cy = 48;
	this->GotoCode = GotoCode;
	PositionGoto.x = PositionGotoX;
	PositionGoto.y = PositionGotoY;

	animation = new std::vector<Animation*>();
	Animation *push = new Animation(IDDarkDoor, 4);
	push->Stop();
	push->SetTime(1 / 15.0f);
	push->SetAutoPlayBack(false);
	animation->push_back(push);

	push = new Animation(IDLightDoor, 4);
	push->Stop();
	push->SetTime(1 / 15.0f);
	push->SetAutoPlayBack(false);
	animation->push_back(push);
}

Door::~Door()
{
	for (auto item : *animation)
		delete item;
	animation->clear();
	delete animation;
}

int Door::OnCollision(Entity *obj, float dt)
{
	Animation *door = (*animation)[SceneManager::GetInstance()->GetCurrentScene()->GetMode() & 1];
	if (door->GetNumberCurrentFrame() != 1)
		return 0;
	if (!DirectInput::GetInstance()->KeyDown(UP_KEY))
		return 0;
	if (obj->GetTag() != Entity::Entity_Tag::player)
		return 0;
	Player *player = Player::GetInstance();
	if (player->GetCurrentState() == PlayerState::NameState::shield_up)
	{
		if (Collision::getInstance()->IsCollide(Entity::GetBoundingBox(), player->GetBoundingBox()))
		{
			SoundManager::GetInstance()->Play(SoundManager::SoundList::door);
			door->SetFrame(2);
			door->Continue();
			player->ChangeState(new PlayerIdleState());
			player->LockState = true;
			Shield::GetInstance()->Update(dt);
		}
	}
	return 0;
}

void Door::Update(float dt)
{
	(*animation)[SceneManager::GetInstance()->GetCurrentScene()->GetMode() & 1]->Update(dt);
}

void Door::Draw()
{
	Player *player = Player::GetInstance();
	if (!player->LockState)
		return;

	Animation *door = (*animation)[SceneManager::GetInstance()->GetCurrentScene()->GetMode() & 1];
	door->DrawInt(Entity::position);
	if (door->GetNumberCurrentFrame() == 1)
	{
		player->LockState = false;
		player->SetPosition(PositionGoto);
		SceneManager::GetInstance()->GetCurrentScene()->SwapMap(GotoCode);
	}
}
