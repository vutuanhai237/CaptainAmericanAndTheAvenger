#include "World11.h"
#include "Framework/DirectInput.h"
#include "Framework/Debug.h"
#include "PlayerIdleState.h"
#include "PlayerRunningState.h"
#include <math.h>

void World11::Update(float dt)
{
	Player *player = Player::GetInstance();
	player->HandleInput();
	player->Update(dt);
	
}

void World11::Draw()
{
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

void World11::Init()
{
	Player::GetInstance()->Init();
	Player::GetInstance()->SetPosition(50.0f, 100.0f);
}

World11::World11()
{
	World11::Init();

}

World11::~World11()
{
	//delete map;
	for (auto item : sprites) {
		delete item;
	}
}
