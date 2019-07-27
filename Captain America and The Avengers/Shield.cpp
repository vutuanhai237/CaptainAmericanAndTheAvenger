#include "Shield.h"
#include "Framework/Debug.h"

Shield *Shield::Instance = NULL;

Shield *Shield::GetInstance()
{
	if (!Instance)
		Instance = new Shield();
	return Instance;
}

void Shield::Release()
{
	delete Instance;
}

D3DXVECTOR2 Shield::GetPosition()
{
	return state->GetVirtualPoint();
}

int Shield::OnCollision(Entity *obj, float dt)
{
	return 0;
}

BoundingBox Shield::GetBoundingBox()
{
	return state->GetBoundingBox();
}

void Shield::Update(float dt)
{
	state->Update(dt);
}

void Shield::Draw()
{
	state->Draw();
}

void Shield::SetShieldState(ShieldState *state)
{
	if (this->state->GetCurrentState() == ShieldState::NameState::ShieldAttack)
	{
		buffer = state;
	}
	else
	{
		delete this->state;
		this->state = state;
	}
}

ShieldState *Shield::GetShieldState()
{
	return state;
}

ShieldState *Shield::GetBufferState()
{
	return buffer;
}

Animation *Shield::GetAnimation()
{
	return shield;
}

Shield::Shield()
{
	Entity::tag = Entity_Tag::shield;
	Entity::type = Entity_Type::player_weapon_type;
	shield = new Animation(0, L"Resources/Shield.png", D3DCOLOR_XRGB(255, 0, 255), 4);
	shield->Stop();
	state = new ShieldState();
}

Shield::~Shield()
{
	delete shield;
	delete state;
}
