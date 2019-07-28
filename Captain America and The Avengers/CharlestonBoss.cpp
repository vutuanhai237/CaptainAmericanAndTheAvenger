#include "CharlestonBoss.h"
#include "Framework/DirectInput.h"
#include "Player.h"
#include "BossWizard.h"
void CharlestonBoss::Init()
{
	Player* player = Player::GetInstance();
	player->Init();
	player->SetPosition(50.0f, 100.0f);
	BossWizard *boss_wizard = BossWizard::GetInstance();
	boss_wizard->Init();
	boss_wizard->SetPosition(50.0f, 100.0f);

}

void CharlestonBoss::Update(float dt)
{
	Player *player = Player::GetInstance();
	// Update zone
//	grid->Update(dt);
	player->HandleInput(dt);
	player->Update(dt);
	BossWizard *boss_wizard = BossWizard::GetInstance();
	boss_wizard->HandleInput(dt);
	boss_wizard->Update(dt);
	auto key = DirectInput::GetInstance();
	if (key->KeyDown(DIK_Q))
		map->SwapMode();
}

void CharlestonBoss::Draw()
{
	map->Draw();
	//grid->DrawActivatedObject();
	Player::GetInstance()->Draw();
}

WorldMap *CharlestonBoss::GetCurrentMap()
{
	return map->GetCurrentMap();
}

Grid * CharlestonBoss::GetCurrentGrid()
{
	return NULL;
}

CharlestonBoss::CharlestonBoss()
{
	map = new CharlestonBossMap();
	cam = Camera::GetInstance();
	cam->SetCameraPosition(0, 0);
	//grid = new Grid(map->GetCurrentMap()->GetMapSize());
	CharlestonBoss::Init();
}

CharlestonBoss::~CharlestonBoss()
{
	delete map;
	//delete grid;
}

