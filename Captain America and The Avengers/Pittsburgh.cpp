#include "Pittsburgh.h"
#include "Player.h"
#include "Shield.h"
#include "ShieldNomalState.h"
#include "Framework/DirectInput.h"

void Pittsburgh::Update(float dt)
{
	Player *player = Player::GetInstance();
	player->HandleInput(dt);
	player->Update(dt);
	Shield::GetInstance()->Update(dt);
	map->GetCurrentGrid()->Update(dt);
	cam->SetCameraPosition(player->GetPosition());

	if (DirectInput::GetInstance()->KeyDown(DIK_Q))
		map->SwapMode();
}

void Pittsburgh::Draw()
{
	map->Draw();
	map->GetCurrentGrid()->DrawActivatedObject();
	Player::GetInstance()->Draw();
}

WorldMap *Pittsburgh::GetCurrentMap()
{
	return map->GetCurrentMap();
}

Grid *Pittsburgh::GetCurrentGrid()
{
	return map->GetCurrentGrid();
}

void Pittsburgh::SwapMap()
{
	map->SwapMode();
}

void Pittsburgh::SwapMap(int code)
{
	map->SwapMap(code);
}

int Pittsburgh::GetMode()
{
	return map->GetMapMode();
}

Pittsburgh::Pittsburgh()
{
	Player* player = Player::GetInstance();
	player->SetPosition(0, 0);
	Shield::GetInstance()->SetShieldState(new ShieldNomalState());
	map = new PittsburghMap();
	cam = Camera::GetInstance();
	cam->Init(map->GetCurrentMap()->GetMapSize());
	cam->SetCameraPosition(player->GetPosition());

	Init();
}

Pittsburgh::~Pittsburgh()
{
	delete map;
}

void Pittsburgh::Init()
{
	Player* player = Player::GetInstance();
	player->SetPosition(32.0f, 848.0f);
	Shield::GetInstance()->SetShieldState(new ShieldNomalState());
	cam->SetCameraPosition(player->GetPosition());
}