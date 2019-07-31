#include "PlayerDieState.h"
#include "Framework//Debug.h"
#include "Shield.h"
#include "SceneManager.h"
#include "Charleston.h"
#include "Shield.h"
#include "ShieldNomalState.h"
PlayerDieState::PlayerDieState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::die);
	this->current_state = PlayerState::NameState::die;
	player->SetVelocity(0, 0);
	this->time_beaten = 0;
	player->time_guc = 0;

	player->OnTheWater = true;
	this->IsGuc = true;
	Shield::GetInstance()->SetShieldState(new ShieldNomalState());
}
PlayerDieState::~PlayerDieState()
{

}

void PlayerDieState::Update(float dt)
{
	
}

void PlayerDieState::Draw()
{
}

BoundingBox PlayerDieState::GetBoundingBox()
{
	Player * player = Player::GetInstance();
	return BoundingBox(
		player->GetPosition(),
		player->GetSize(),
		player->GetVelocityX(),
		player->GetVelocityY()
	);

}

void PlayerDieState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->time_guc += dt;
	auto keyboard = DirectInput::GetInstance();
	if (keyboard->KeyDown(DIK_H)) {
		player->hp = PLAYER_HP;
		player->GetCurrentAnimation()->ResetAnimation();
		player->ChangeState(new PlayerIdleState());
		return;
	}
	if (player->GetCurrentAnimation()->GetNumberCurrentFrame() == 1 && this->IsGuc)
	{
		player->GetCurrentAnimation()->Pause(TIME_GUC_BEFORE_NAM);
		IsGuc = false;
	}
	if (player->GetCurrentAnimation()->GetNumberCurrentFrame() == 2)
	{
		player->GetCurrentAnimation()->Pause(100000);
	}

}
