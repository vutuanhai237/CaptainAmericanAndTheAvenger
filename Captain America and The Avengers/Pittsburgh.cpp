#include "Pittsburgh.h"
#include "Player.h"
#include "Shield.h"
#include "ShieldNomalState.h"
#include "Framework/SoundManager.h"
#include "Framework/DirectInput.h"
#include "PittsburghBoss.h"
#include "GrayRocketRobot.h"
#include "GreenSoldier.h"
#include "SceneManager.h"
#include "ItemsHolder.h"
#include <fstream>
#include "PlayerIdleState.h"
#include "Grid.h"
void Pittsburgh::Update(float dt)
{
	Scene::Update(dt);
	Player *player = Player::GetInstance();
	player->HandleInput(dt);
	player->Update(dt);
	Shield::GetInstance()->Update(dt);
	map->GetCurrentGrid()->Update(dt);
	cam->SetCameraPosition(player->GetPosition());

	if (DirectInput::GetInstance()->KeyDown(DIK_Q))
		map->SwapMode();
	
	if (this->UpdateOneTime == false) {
		if (cam->GetCameraPosition().x >= 255-3 && cam->GetCameraPosition().x <= 255+3 
			&& cam->GetCameraPosition().y <= 3) {
			map->GetCurrentGrid()->ForceEnemyExplode();
			cam->SetCameraFreeze(true);
			this->UpdateOneTime = true;
			SoundManager::GetInstance()->Stop(SoundManager::SoundList::main_theme);
			SoundManager::GetInstance()->PlayRepeat(SoundManager::SoundList::actiton_theme);
		}
	}
	this->timer += dt;
	this->timer2 += dt;
	if (cam->GetCameraFreeze()) {
		if (player->IsBornRocketRobot && this->timer2 > 3.0f) {
			(map->GetCurrentGrid())->AddObject2Cell(new GrayRocketRobot(D3DXVECTOR2(cam->GetCameraPosition().x + GAME_SCREEN_WIDTH + 8, 80), D3DXVECTOR2(230, 80), 0));
			player->IsBornRocketRobot = false;
			this->timer2 = 0;

		}
		if (player->IsBornSoldier && this->timer > 3.0f) {
			(map->GetCurrentGrid())->AddObject2Cell(new GreenSoldier(3, D3DXVECTOR2(cam->GetCameraPosition().x - 8, 75), 0));
			player->IsBornSoldier = false;
			this->timer = 0;
		}
	}
	if (player->number_rocket_robot >= 3) {
		cam->SetCameraFreeze(false);
		player->number_rocket_robot = 0;
		player->number_soldier = 0;
		map->GetCurrentGrid()->ForceEnemyExplode();

		SoundManager::GetInstance()->Stop(SoundManager::SoundList::actiton_theme);
		SoundManager::GetInstance()->PlayRepeat(SoundManager::SoundList::main_theme);

	}
	if (DirectInput::GetInstance()->KeyDown(DIK_GRAVE))
		SceneManager::GetInstance()->ReplaceScene(new Pittsburgh());
	if (IsExitAble && IsInsideExitZone())
		SceneManager::GetInstance()->ReplaceScene(new PittsburghBoss());
	// Cheat Fast next map
	if (DirectInput::GetInstance()->KeyDown(DIK_N))
	{
		if (cam->GetCameraFreeze()) {
			cam->SetCameraFreeze(false);
		}
		SceneManager::GetInstance()->ReplaceScene(new PittsburghBoss());
	}
}

void Pittsburgh::Draw()
{
	map->Draw();
	map->GetCurrentGrid()->DrawActivatedObject();
	Player *player = Player::GetInstance();
	player->Draw();
	if (player->time_guc >= TIME_DIE)
	{
		player->time_guc = 0;
		player->hp = PLAYER_HP;
		player->ChangeState(new PlayerIdleState());
		SceneManager::GetInstance()->ReplaceScene(new Pittsburgh());
		return;
	}
	Scene::Draw();
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
	ExitZone.top = 224;
	ExitZone.bottom = 48;
	ExitZone.left = 976;
	ExitZone.right = 1008;
	cam = Camera::GetInstance();
	cam->Init(map->GetCurrentMap()->GetMapSize());
	cam->SetCameraPosition(player->GetPosition());
	this->UpdateOneTime = false;
	this->timer = 3;
	this->timer2 = 3;
	Init();
	// sound 
	SoundManager::GetInstance()->StopAllSound();
	SoundManager::GetInstance()->PlayRepeat(SoundManager::SoundList::main_theme);
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