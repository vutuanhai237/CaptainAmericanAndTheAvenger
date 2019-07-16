#include "CharlestonBoss.h"
#include "Framework/DirectInput.h"

void CharlestonBoss::Update(float dt)
{
	auto key = DirectInput::GetInstance();
	if (key->KeyDown(DIK_Q))
		map->SwapMode();
}

void CharlestonBoss::Draw()
{
	map->Draw();
}

CharlestonBoss::CharlestonBoss()
{
	map = new CharlestonBossMap();
	cam = Camera::GetInstance();
}

CharlestonBoss::~CharlestonBoss()
{
	delete map;
}
