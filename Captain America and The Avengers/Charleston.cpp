#include <d3dx9.h>
#include <fstream>
#include "Charleston.h"
#include "Framework/DirectInput.h"
#include "Framework/Debug.h"
#include "Camera.h"
#include "WorldMap.h"
#include "Player.h"
#include "Shield.h"
#include "Framework/DirectInput.h"
#include "SceneManager.h"
#include "CharlestonBoss.h"
#include "RedRocketRobot.h"

void Charleston::Update(float dt)
{
	
	Player *player = Player::GetInstance();
	// Update zone
	map->Update(dt);

	grid->Update(dt);

	player->HandleInput(dt);
	player->Update(dt);
	Shield::GetInstance()->Update(dt);
	cam->SetCameraPosition(player->GetPosition());

	auto tmp = DirectInput::GetInstance();
	if (tmp->KeyDown(DIK_N))
	{
		CharlestonBoss *boss = new CharlestonBoss();
		SceneManager::GetInstance()->ReplaceScene(boss);
	}
}

void Charleston::Draw()
{
	map->Draw();
	Player::GetInstance()->Draw();
	grid->DrawActivatedObject();
}

WorldMap * Charleston::GetCurrentMap()
{
	return this->map;
}

void Charleston::Init()
{
	Player* player = Player::GetInstance();
	player->Init();
	player->SetPosition(50.0f, 100.0f);

	int n, m;
	int tag;
	fstream data(L"Resources/Map/charleston_map_items_enemy.txt", ios_base::in);
	int *obj;
	data >> n;
	for (int i = 0; i < n; i++)
	{
		data >> tag;
		switch (tag)
		{
		case Entity::Entity_Tag::redrobotrocket:
			m = 8;
			break;
		default:
			continue;
		}
		obj = new int[m];
		obj[0] = tag;
		for (int j = 1; j < m; j++)
			data >> obj[j];
		grid->AddObject2Cell(obj[1], obj[2], obj);
	}
}

Charleston::Charleston()
{
	map = new CharlestonMap();
	cam = Camera::GetInstance();
	grid = new Grid(map->GetMapSize());
	Charleston::Init();
}

Charleston::~Charleston()
{
	delete map;
	delete grid;
}
