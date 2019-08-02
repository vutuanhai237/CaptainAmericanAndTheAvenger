#include "PittsburghBoss.h"
#include "Player.h"
#include "Shield.h"
#include "ShieldNomalState.h"
#include "SceneManager.h"
#include "Charleston.h"
#include "BossGragas.h"
void PittsburghBoss::Update(float dt)
{
	Scene::Update(dt);
	Player *player = Player::GetInstance();
	// Update zone
	
	map->Update(dt);

	player->HandleInput(dt);
	player->Update(dt);

	Shield::GetInstance()->Update(dt);
	grid->Update(dt);
	cam->SetCameraPosition(player->GetPosition());

	if (IsExitAble && IsInsideExitZone())
		SceneManager::GetInstance()->ReplaceScene(new Charleston());
	// Cheat Fast next map
	if (DirectInput::GetInstance()->KeyDown(DIK_N))
		SceneManager::GetInstance()->ReplaceScene(new Charleston());
}

void PittsburghBoss::Draw()
{
	map->Draw();
	grid->DrawActivatedObject();
	Player::GetInstance()->Draw();
	if (Player::GetInstance()->time_guc >= TIME_DIE) {
		Player::GetInstance()->time_guc = 0;
		SceneManager::GetInstance()->ReplaceScene(new PittsburghBoss());
		return;
	}
}

WorldMap *PittsburghBoss::GetCurrentMap()
{
	return map;
}

Grid * PittsburghBoss::GetCurrentGrid()
{
	return grid;
}

PittsburghBoss::PittsburghBoss()
{
	map = new PittsburghBossMap();
	cam = Camera::GetInstance();
	cam->Init(map->GetMapSize());
	grid = new Grid(map->GetMapSize());
	ExitZone.top = GAME_SCREEN_HEIGHT;
	ExitZone.bottom = 0;
	ExitZone.left = 0;
	ExitZone.right = GAME_SCREEN_WIDTH;
	grid->AddObject2Cell(Player::GetInstance());
	grid->AddObject2Cell(Shield::GetInstance());
	Scene::Mode = 1;
	Init();
}

PittsburghBoss::~PittsburghBoss()
{
	delete map;
	delete grid;
	
}

void PittsburghBoss::Init()
{
	Player* player = Player::GetInstance();
	player->Init();
	player->SetPosition(50.0f, 100.0f);
	grid->AddObject2Cell(player);
	Shield* shield = Shield::GetInstance();
	grid->AddObject2Cell(shield);

	cam->SetCameraPosition(player->GetPosition());
	BossGragas *boss = BossGragas::GetInstance();
	grid->AddObject2Cell(boss);

}
