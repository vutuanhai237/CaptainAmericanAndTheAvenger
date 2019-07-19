#include "Shield.h"

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
	this->state = state;
}

Animation * Shield::GetAnimation()
{
	return shield;
}

Shield::Shield()
{
	shield = new Animation(0, L"Resources/Shield.png", D3DCOLOR_XRGB(255, 0, 255), 4);
	shield->Stop();
	state = new ShieldState();
}

Shield::~Shield()
{
	delete shield;
	delete state;
}
