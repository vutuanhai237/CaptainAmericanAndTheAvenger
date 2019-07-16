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

void Charleston::Init()
{
	Player::GetInstance()->Init();
	Player::GetInstance()->SetPosition(50.0f, 100.0f);
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
