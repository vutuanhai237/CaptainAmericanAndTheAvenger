#include "Charleston.h"
#include "Framework/DirectInput.h"
#include "Framework/Debug.h"
#include <d3dx9.h>
#include "Camera.h"
#include "WorldMap.h"
#include "Player.h"

#include "Framework/DirectInput.h"
#include "SceneManager.h"
#include "CharlestonBoss.h"

void Charleston::Update(float dt)
{
	map->Update(dt);
	Player *player = Player::GetInstance();
	player->HandleInput(dt);
	player->Update(dt);
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
	
	Player *player = Player::GetInstance();

	if (player->GetMoveDirection()) {
		player->GetCurrentAnimation()->SetScale(1, 1);
		player->SetVelocityX(-abs(player->GetVelocityX()));
	}
	else {

		player->GetCurrentAnimation()->SetScale(-1, 1);
		player->SetVelocityX(abs(player->GetVelocityX()));
	}
	player->Draw();

	
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
	player->SetPositionIdle(player->GetPosition());

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
