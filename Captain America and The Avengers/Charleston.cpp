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
	Player::GetInstance()->Draw();
	bot1->Draw();	
}

WorldMap * Charleston::GetCurrentMap()
{
	return this->map;
}

void Charleston::Init()
{
	Player* player = Player::GetInstance();
	player->Init();
	player->SetPosition(300.0f, 100.0f);

	bot1 = new RedRocketRobot(
		RedRocketRobot::Level::normal,
		D3DXVECTOR2(400.0f, 150.0f),
		D3DXVECTOR2(300.0f, 150.0f),
		D3DXVECTOR2(200.0f, 150.0f)
	);
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
