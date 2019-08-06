#include "PlayerPunchingState.h"
#include "PlayerArm.h"
#include "SceneManager.h"
#include "Framework/SoundManager.h"
PlayerPunchingState::PlayerPunchingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::punching);
	this->current_state = PlayerState::NameState::punching;
	player->SetTimeBuffer(0);
	SoundManager::GetInstance()->Play(SoundManager::SoundList::player_punch_kick);
	SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(new PlayerArm());
}
PlayerPunchingState::~PlayerPunchingState()
{

}

void PlayerPunchingState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->SetVelocity(0, 0);
}

void PlayerPunchingState::Draw()
{

}

BoundingBox PlayerPunchingState::GetBoundingBox()
{
	Player * player = Player::GetInstance();
	return BoundingBox(
		player->GetPosition(),
		player->GetSize(),
		player->GetVelocityX(),
		player->GetVelocityY()
	);
}

void PlayerPunchingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (player->GetCurrentAnimation()->GetNumberCurrentFrame() == 2)
	{
		player->GetCurrentAnimation()->Pause(TIME_WAIT_PUNCHING);
	}
	// Dừng throwing khi time out, chuyển về idle
	if (player->GetCurrentAnimation()->GetAnimationTime() >= TIME_PUNCHING)
	{
		player->GetCurrentAnimation()->SetAnimationTime(0.0f);
		player->GetCurrentAnimation()->SetFrame(1);
		player->ChangeState(new PlayerIdleState());
		return;
	}
	else 
	{
		return;
	}
	// Ưu tiên các trạng thái khái
	if (keyboard->KeyDown(RIGHT_KEY))
	{
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		return;
	}

	if (keyboard->KeyDown(LEFT_KEY))
	{
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		return;
	}

	if (keyboard->KeyDown(ATTACK_KEY))
	{
		return;
	}
	if (keyboard->KeyDown(JUMP_KEY))
	{
		player->ChangeState(new PlayerJumpingState());
		return;
	}

	if (keyboard->KeyDown(UP_KEY)) 
	{
		player->ChangeState(new PlayerShieldUpState());
		return;
	}

	if (keyboard->KeyDown(DOWN_KEY))
	{
		player->ChangeState(new PlayerDuckingState());
		return;
	}
	player->ChangeState(new PlayerIdleState());
	return;
}