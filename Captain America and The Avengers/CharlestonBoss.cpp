#include "CharlestonBoss.h"
#include "Player.h"
#include "Shield.h"
#include "OnOffSwitch.h"
#include "SceneManager.h"
#include "Framework/DirectInput.h"
#include <fstream>
#include "Pittsburgh.h"
#include "ShieldNomalState.h"
#include "BossWizard.h"
#include "PlayerIdleState.h"
#include "LaserBullet.h"
#include "Framework/SoundManager.h"
void CharlestonBoss::Update(float dt)
{
	Player *player = Player::GetInstance();
	player->HandleInput(dt);
	player->Update(dt);
	Shield::GetInstance()->Update(dt);
	grid->Update(dt);
	BossWizard *boss = BossWizard::GetInstance();
	Camera::GetInstance()->SetCameraFreeze(false);
	this->time_count += dt;
	if (this->time_count >= 4.0f && this->count_bullet == 0) {
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
			new LaserBullet(
				D3DXVECTOR2(256, 63),
				Entity::Entity_Direction::RightToLeft,
				-1
			)
		);
		this->count_bullet++;
	}
	if (this->time_count >= 8.0f && this->count_bullet == 1) {
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
			new LaserBullet(
				D3DXVECTOR2(0, 63),
				Entity::Entity_Direction::LeftToRight,
				abs(player->GetPosition().y - 54)
			)
		);
		this->count_bullet++;
	}
	if (this->time_count >= 12.0f && this->count_bullet == 2) {
		SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
			new LaserBullet(
				D3DXVECTOR2(256, 63),
				Entity::Entity_Direction::RightToLeft,
				-1
			)
		);
		this->count_bullet++;
	}
	//if (this->time_count >= 16.0f && this->count_bullet == 3) {
	if (this->count_bullet == 0) {
		grid->AddObject2Cell(boss);
		boss->Init();
		float x = rand() % 170 + 50;
		boss->SetPosition(x, 200.0f);
		this->count_bullet++;

	}
	if (IsExitAble && IsInsideExitZone())
		SceneManager::GetInstance()->ReplaceScene(new Pittsburgh());
	// Cheat Fast next map
	if (DirectInput::GetInstance()->KeyDown(DIK_N))
		SceneManager::GetInstance()->ReplaceScene(new Pittsburgh());
}

void CharlestonBoss::Draw()
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
		SceneManager::GetInstance()->ReplaceScene(new CharlestonBoss());
		return;
	}	
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

int CharlestonBoss::GetMode()
{
	return map->GetMode();
}

CharlestonBoss::CharlestonBoss() : Scene()
{
	Player* player = Player::GetInstance();
	player->SetPosition(24.0f, 75.0f);
	Shield::GetInstance()->SetShieldState(new ShieldNomalState());
	BossWizard* boss = BossWizard::GetInstance();
	
	this->time_count = 0;
	this->count_bullet = 0;
	this->UpdateOneTime = false;
	map = new CharlestonBossMap();
	cam = Camera::GetInstance();
	cam->SetCameraPosition(player->GetPosition());
	cam->Init(map->GetMapSize());
	grid = new Grid(map->GetMapSize());
	ExitZone.top = GAME_SCREEN_HEIGHT;
	ExitZone.bottom = 0;
	ExitZone.left = 0;
	ExitZone.right = GAME_SCREEN_WIDTH;
	grid->AddObject2Cell(player);
	grid->AddObject2Cell(Shield::GetInstance());
	Init();
	// sound 
	SoundManager::GetInstance()->StopAllSound();
	SoundManager::GetInstance()->PlayRepeat(SoundManager::SoundList::boss_wizard_theme);
}

CharlestonBoss::~CharlestonBoss()
{
	delete map;
	delete grid;
	BossWizard::GetInstance()->Release();
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
