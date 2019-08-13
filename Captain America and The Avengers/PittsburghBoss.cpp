#include "PittsburghBoss.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "Shield.h"
#include "ShieldNomalState.h"
#include "SceneManager.h"
#include "Charleston.h"
#include "BossGragas.h"
#include "Framework/SoundManager.h"

void PittsburghBoss::Update(float dt)
{
	Scene::Update(dt);
	Player *player = Player::GetInstance();
	Camera::GetInstance()->SetCameraFreeze(false);
	map->Update(dt);
	player->HandleInput(dt);
	player->Update(dt);
	Shield::GetInstance()->Update(dt);
	grid->Update(dt);
	cam->SetCameraPosition(player->GetPosition());
	if (IsExitAble && IsInsideExitZone())
	{
		SceneManager::GetInstance()->ReplaceScene(new Charleston());
	}
	// Cheat Fast next map
	if (DirectInput::GetInstance()->KeyDown(DIK_N))
	{
		SceneManager::GetInstance()->ReplaceScene(new Charleston());
	}
}

void PittsburghBoss::Draw()
{
	map->Draw();
	grid->DrawActivatedObject();
	Player *player = Player::GetInstance();
	player->Draw();
	if (player->time_guc >= TIME_DIE) 
	{
		player->time_guc = 0;
		player->hp = PLAYER_HP;
		player->ChangeState(new PlayerIdleState());
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
	ExitZone.top = (LONG)GAME_SCREEN_HEIGHT;
	ExitZone.bottom = 0;
	ExitZone.left = 0;
	ExitZone.right = (LONG)GAME_SCREEN_WIDTH;
	grid->AddObject2Cell(Player::GetInstance());
	grid->AddObject2Cell(Shield::GetInstance());
	Scene::Mode = 1;
	Init();
	SoundManager::GetInstance()->StopAllSound();
	SoundManager::GetInstance()->PlayRepeat(SoundManager::SoundList::boss_gragas_theme);
}

PittsburghBoss::~PittsburghBoss()
{
	delete map;
	delete grid;
	//BossGragas::GetInstance()->Release();	
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
