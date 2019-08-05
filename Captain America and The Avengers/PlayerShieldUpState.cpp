#include "PlayerShieldUpState.h"
#include "Framework//Debug.h"
#include "ShieldUpState.h"
#include "Shield.h"
PlayerShieldUpState::PlayerShieldUpState()
{
	Player* player = Player::GetInstance();
	player->SetSize(24, 43);

	player->SetCurrentState(PlayerState::NameState::shield_up);
	player->SetTimeBuffer(0);
	this->current_state = PlayerState::NameState::shield_up;
	Shield::GetInstance()->SetShieldState(new ShieldUpState());
}
PlayerShieldUpState::~PlayerShieldUpState()
{

}

void PlayerShieldUpState::Update(float dt)
{
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	player->SetVelocity(0, 0);
}

void PlayerShieldUpState::Draw()
{
}

BoundingBox PlayerShieldUpState::GetBoundingBox()
{
	Player * player = Player::GetInstance();
	return BoundingBox(
		player->GetPosition(),
		player->GetSize(),
		player->GetVelocityX(),
		player->GetVelocityY()
	);

}

void PlayerShieldUpState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	if (!player->IsCollisionWithPlatform(dt))
	{
		if (!player->IsCollisionWithGround(dt)) {
			if (!player->IsCollisionWithWall(dt)) {
				if (!player->IsCollisionWithWater(dt)) {
					player->ChangeState(new PlayerJumpingDownState());
					return;
				}
			}

		}
	}
	// Nếu vẫn up và down cùng lúc thì về idle
	if (keyboard->KeyPress(UP_KEY) && keyboard->KeyPress(DOWN_KEY)) {
		player->ChangeState(new PlayerIdleState());

		return;
	}
	// Ưu tiên các trạng thái khái
	if (keyboard->KeyDown(RIGHT_KEY)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		return;
	}

	if (keyboard->KeyDown(LEFT_KEY)) {
		player->ChangeState(new PlayerRunningState());
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		return;
	}
	if (keyboard->KeyDown(ATTACK_KEY)) {
		player->ChangeState(new PlayerThrowingState());
		return;
	}
	if (keyboard->KeyDown(JUMP_KEY)) {
		player->ChangeState(new PlayerJumpingState());
		return;
	}
	// Nếu vẫn nhấn thì giữ nguyên trạng thái
	if (keyboard->KeyPress(UP_KEY)) {
		return;
	}
	player->ChangeState(new PlayerIdleState());
	return;
}
