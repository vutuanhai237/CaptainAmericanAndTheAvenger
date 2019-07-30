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
#include "ItemsHolder.h"
#include "BossWizard.h"
void Charleston::Update(float dt)
{
	
	Player *player = Player::GetInstance();
	// Update zone
	map->Update(dt);

	player->HandleInput(dt);
	player->Update(dt);

	Shield::GetInstance()->Update(dt);
	grid->Update(dt);
	cam->SetCameraPosition(player->GetPosition());

	if (IsExitAble && IsInsideExitZone())
		SceneManager::GetInstance()->ReplaceScene(new CharlestonBoss());
	// Cheat Fast next map
	if (DirectInput::GetInstance()->KeyDown(DIK_N))
		SceneManager::GetInstance()->ReplaceScene(new CharlestonBoss());
	
}

void Charleston::Draw()
{
	map->Draw();
	grid->DrawActivatedObject();
	if (Scene::IsExitAble)
		DrawExit();
	Player::GetInstance()->Draw();
	if (Player::GetInstance()->time_guc >= TIME_DIE) {
		Player::GetInstance()->time_guc = 0;
		SceneManager::GetInstance()->ReplaceScene(new Charleston());
		return;
	}
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
		default:
			continue;
		}
	}

}

void Charleston::DrawExit()
{
	if (FrameExitCounter == 0)
	{
		FirstExitPosition = Player::GetInstance()->GetPosition();
		FirstExitPosition.y += PLAYER_SIZE_HEIGHT;
	}
	if (FrameExitCounter < 50)
		exit->DrawInt(FirstExitPosition);
	else
	{
		if (FrameExitCounter == 50)
		{
			exit->SetPosition(64, 24);
		}

		if (FrameExitCounter >> 4 & 1)
			exit->Draw();
	}
	FrameExitCounter++;
}

Charleston::Charleston() : Scene()
{
	map = new CharlestonMap();
	cam = Camera::GetInstance();
	cam->Init(map->GetMapSize());
	grid = new Grid(map->GetMapSize());
	exit = new Sprite(L"Resources/exit.png", D3DCOLOR_XRGB(255, 0, 255));
	FrameExitCounter = 0;
	ExitZone.top = 128;
	ExitZone.bottom = 48;
	ExitZone.left = 1968;
	ExitZone.right = 2016;

	Charleston::Init();
}

Charleston::~Charleston()
{
	delete map;
	delete grid;
}
