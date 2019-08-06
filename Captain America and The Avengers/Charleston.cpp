#include <fstream>
#include "Charleston.h"
#include "Framework/DirectInput.h"
#include "Framework/SoundManager.h"
#include "Framework/DirectInput.h"
#include "SceneManager.h"
#include "CharlestonBoss.h"
#include "RedRocketRobot.h"
#include "ItemsHolder.h"
#include "BlueSoldier.h"
#include "PlayerIdleState.h"
#include "BossWizard.h"
#include "Camera.h"
#include "Player.h"
#include "Shield.h"
void Charleston::Update(float dt)
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

	
	if (this->UpdateOneTime == false) {
		if (player->GetPosition().x >= 415 && player->GetPosition().y < 120) {
			grid->ForceEnemyExplode();
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
			grid->AddObject2Cell(new RedRocketRobot(3, D3DXVECTOR2(cam->GetCameraPosition().x + GAME_SCREEN_WIDTH + 8, 70), D3DXVECTOR2(240, 70), 0));
			player->IsBornRocketRobot = false;
			this->timer2 = 0;

		}
		if (player->IsBornSoldier && this->timer > 3.0f) {
			grid->AddObject2Cell(new BlueSoldier(2, D3DXVECTOR2(cam->GetCameraPosition().x-8, 70), 0));
			player->IsBornSoldier = false;
			this->timer = 0;
		}
	}
	if (player->number_rocket_robot >= 3 && player->number_soldier >= 3) {
		cam->SetCameraFreeze(false);
		grid->ForceEnemyExplode();
		SoundManager::GetInstance()->Stop(SoundManager::SoundList::actiton_theme);
		SoundManager::GetInstance()->PlayRepeat(SoundManager::SoundList::main_theme);
		player->number_rocket_robot = 0;	
		player->number_soldier = 0;
	}
	if (IsExitAble && IsInsideExitZone())
		SceneManager::GetInstance()->ReplaceScene(new CharlestonBoss());
	if (DirectInput::GetInstance()->KeyDown(DIK_GRAVE))
		SceneManager::GetInstance()->ReplaceScene(new Charleston());
	// Cheat Fast next map
	if (DirectInput::GetInstance()->KeyDown(DIK_N))
	{
		if (cam->GetCameraFreeze()) {
			cam->SetCameraFreeze(false);
		}
		SceneManager::GetInstance()->ReplaceScene(new CharlestonBoss());
	}
}

void Charleston::Draw()
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
		if (cam->GetCameraFreeze()) {
			cam->SetCameraFreeze(false);
		}
		SceneManager::GetInstance()->ReplaceScene(new Charleston());
		return;
	}
	Scene::Draw();
}

WorldMap * Charleston::GetCurrentMap()
{
	return this->map;
}

Grid *Charleston::GetCurrentGrid()
{
	return grid;
}

void Charleston::Init()
{
	Player* player = Player::GetInstance();
	player->Init();
	player->SetPosition(50.0f, 100.0f);
	cam->SetCameraPosition(player->GetPosition());
	int n, m;
	int tag, posX, posY, tmp;
	fstream data(L"Resources/Map/charleston_map_items_enemy.txt", ios_base::in);
	int *obj;
	Entity *item;
	ItemsHolder *holder;
	data >> n;
	for (int i = 0; i < n; i++)
	{
		data >> tag >> posX >> posY;
		switch (tag)
		{
		case Entity::Entity_Tag::item_container:
			holder = new ItemsHolder(posX, posY);
			data >> m;
			for (int i = 0; i < m; i++)
			{
				data >> tmp;
				holder->PutOnItem(tmp);
			}
			grid->AddObject2Cell(holder);
			continue;
		case Entity::Entity_Tag::redrobotrocket:
			obj = new int[7];
			obj[0] = tag;
			obj[1] = posX;
			obj[2] = posY;
			data >> obj[3] >> obj[4] >> obj[5] >> obj[6];
			grid->AddObject2Cell(posX, posY, obj);
			continue;
		case Entity::Entity_Tag::blue_soldier:
			obj = new int[5];
			obj[0] = tag;
			obj[1] = posX;
			obj[2] = posY;
			data >> obj[3] >> obj[4];
			grid->AddObject2Cell(posX, posY, obj);
			continue;
		case Entity::Entity_Tag::green_soldier:
			obj = new int[5];
			obj[0] = tag;
			obj[1] = posX;
			obj[2] = posY;
			data >> obj[3] >> obj[4];
			grid->AddObject2Cell(posX, posY, obj);
			continue;
		case Entity::Entity_Tag::gray_robot:
			obj = new int[4];
			obj[0] = tag;
			obj[1] = posX;
			obj[2] = posY;
			data >> obj[3];
			grid->AddObject2Cell(posX, posY, obj);
			continue;
		case Entity::Entity_Tag::cannon:
			obj = new int[4];
			obj[0] = tag;
			obj[1] = posX;
			obj[2] = posY;
			data >> obj[3];
			grid->AddObject2Cell(posX, posY, obj);
			continue;
		default:
			continue;
		}
	}

}

Charleston::Charleston() : Scene()
{
	map = new CharlestonMap();
	cam = Camera::GetInstance();
	cam->Init(map->GetMapSize());
	grid = new Grid(map->GetMapSize());
	ExitZone.top = 128;
	ExitZone.bottom = 48;
	ExitZone.left = 1968;
	ExitZone.right = 2016;
	grid->AddObject2Cell(Player::GetInstance());
	grid->AddObject2Cell(Shield::GetInstance());
	Scene::Mode = 1;
	this->timer = 0.0f;
	this->UpdateOneTime = false;
	this->timer2 = 0.0f;
	Charleston::Init();
	// sound 
	SoundManager::GetInstance()->StopAllSound();
	SoundManager::GetInstance()->PlayRepeat(SoundManager::SoundList::main_theme);
}

Charleston::~Charleston()
{
	delete map;
	delete grid;
}
