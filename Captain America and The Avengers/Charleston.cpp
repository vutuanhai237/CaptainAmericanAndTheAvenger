#include "Charleston.h"
#include "Framework/DirectInput.h"
#include "Framework/Debug.h"
#include <d3dx9.h>
#include "Camera.h"
#include "WorldMap.h"
#include "Player.h"
#include "Shield.h"
#include "Framework/DirectInput.h"
#include "SceneManager.h"
#include "CharlestonBoss.h"
#include "RedRocketRobot.h"
RedRocketRobot * bot1;
void Charleston::Update(float dt)
{
	
	Player *player = Player::GetInstance();
	// Update zone
	map->Update(dt);
	player->HandleInput(dt);
	player->Update(dt);
	Shield::GetInstance()->Update(dt);
	cam->SetCameraPosition(player->GetPosition());
	bot1->Update(dt);


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
	
	Player *player = Player::GetInstance();
	Shield *shield = Shield::GetInstance();

	if (player->GetMoveDirection()) {
		player->GetCurrentAnimation()->SetScale(1, 1);
		shield->GetAnimation()->SetScale(1, 1);
	}
	else {

		player->GetCurrentAnimation()->SetScale(-1, 1);
		shield->GetAnimation()->SetScale(-1, 1);
	}
	if (bot1->GetMoveDirection()) {
		bot1->GetCurrentAnimation()->SetScale(1, 1);
	}
	else {
		bot1->GetCurrentAnimation()->SetScale(-1, 1);
	}
	bot1->Draw();

	player->Draw();
	shield->Draw();
}

WorldMap * Charleston::GetCurrentMap()
{
	return this->map;
}

void Charleston::Init()
{
	Player* player = Player::GetInstance();
	player->Init();
	player->SetPosition(48.0f, 100.0f); //48:69

	bot1 = new RedRocketRobot();
	bot1->SetPosition(50.0f, 150.0f);
	exit = new Animation(111, L"Resources\\exit.png", D3DCOLOR_XRGB(255,0,255), 1);
	//vector<Entity*> obj = *SceneManager::GetInstance()->GetCurr
	i = 0;
	exit->SetPosition(48.0f, 27.0f);
}

Charleston::Charleston()
{
	map = new CharlestonMap();
	cam = Camera::GetInstance();
	Charleston::Init();
}

Charleston::~Charleston()
{
	delete map;
}
