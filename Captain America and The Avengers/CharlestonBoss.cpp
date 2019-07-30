#include "CharlestonBoss.h"
#include "Player.h"
#include "Shield.h"
#include "OnOffSwitch.h"
#include "SceneManager.h"
#include "Framework/DirectInput.h"
#include <fstream>
#include "BossWizard.h"
void CharlestonBoss::Update(float dt)
{
	Player *player = Player::GetInstance();
	grid->Update(dt);
	player->HandleInput(dt);
	player->Update(dt);
	Shield::GetInstance()->Update(dt);

	BossWizard *boss = BossWizard::GetInstance();
	boss->Update(dt);
	// Cheat Fast next map
	if (DirectInput::GetInstance()->KeyDown(DIK_N))
		SceneManager::GetInstance()->ReplaceScene(new CharlestonBoss());
}

void CharlestonBoss::Draw()
{
	map->Draw();
	grid->DrawActivatedObject();
	Player::GetInstance()->Draw();
	BossWizard::GetInstance()->Draw();
}

WorldMap *CharlestonBoss::GetCurrentMap()
{
	return map->GetCurrentMap();
}

Grid *CharlestonBoss::GetCurrentGrid()
{
	return grid;
}

void CharlestonBoss::SwapMap()
{
	map->SwapMode();
	Mode = Mode ^ 1;
}

void CharlestonBoss::SwapMap(int code)
{
	if (code == CharlestonBossMap::MapMode::Dark)
	{
		map->SwapMode(CharlestonBossMap::MapMode::Dark);
		Mode = 0;
	}
	else if (code == CharlestonBossMap::MapMode::Light)
	{
		Mode = 1;
		map->SwapMode(CharlestonBossMap::MapMode::Light);
	}
}

CharlestonBoss::CharlestonBoss() : Scene()
{
	Player* player = Player::GetInstance();
	player->Init();
	player->SetPosition(100.0f, 100.0f);

	BossWizard* boss = BossWizard::GetInstance();
	boss->Init();
	boss->SetPosition(24.0f, 75.0f);

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
	delete grid;
}

void CharlestonBoss::Init()
{
	int n;
	int tag, posX, posY, tmp;
	Entity *item;

	fstream data(L"Resources/Map/charleston_boss_item_enemy.txt", ios_base::in);
	data >> n;
	for (int i = 0; i < n; i++)
	{
		data >> tag >> posX >> posY;
		switch (tag)
		{
		case Entity::Entity_Tag::on_off_switch:
			item = new OnOffSwitch(posX, posY);
			grid->AddObject2Cell(item);
			break;
		default:
			break;
		}
	}
}
