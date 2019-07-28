#include "CharlestonBoss.h"
#include "Player.h"
#include "Shield.h"
#include "Framework/DirectInput.h"

void CharlestonBoss::Update(float dt)
{
	Player *player = Player::GetInstance();
	grid->Update(dt);
	player->HandleInput(dt);
	player->Update(dt);
	Shield::GetInstance()->Update(dt);
	//cam->SetCameraPosition(player->GetPosition());

	auto key = DirectInput::GetInstance();
	if (key->KeyDown(DIK_Q))
		map->SwapMode();
}

void CharlestonBoss::Draw()
{
	map->Draw();
	grid->DrawActivatedObject();
	Player::GetInstance()->Draw();
}

WorldMap *CharlestonBoss::GetCurrentMap()
{
	return map->GetCurrentMap();
}

Grid *CharlestonBoss::GetCurrentGrid()
{
	return grid;
}

CharlestonBoss::CharlestonBoss() : Scene()
{
	Player* player = Player::GetInstance();
	player->Init();
	player->SetPosition(50.0f, 100.0f);

	map = new CharlestonBossMap();
	cam = Camera::GetInstance();
	cam->SetCameraPosition(player->GetPosition());
	cam->Init(map->GetMapSize());
	grid = new Grid(map->GetMapSize());
	ExitZone.top = GAME_SCREEN_HEIGHT;
	ExitZone.bottom = 0;
	ExitZone.left = 0;
	ExitZone.right = GAME_SCREEN_WIDTH;

	Init();
}

CharlestonBoss::~CharlestonBoss()
{
	delete map;
}

void CharlestonBoss::Init()
{
}
