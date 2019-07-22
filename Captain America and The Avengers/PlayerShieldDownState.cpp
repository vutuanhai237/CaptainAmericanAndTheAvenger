#include "PlayerShieldDownState.h"
#include "Framework//Debug.h"
#include "PlayerFlowingState.h"
#include "Shield.h"
#include "ShieldDownState.h"

PlayerShieldDownState::PlayerShieldDownState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::shield_down);
	player->SetTimeBuffer(0);
	player->IsJumping = false;
	player->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
	player->SetVelocityY(VELOCITY_Y);

	this->IsNhunsLen = false;
	this->current_state = PlayerState::NameState::shield_down;
	this->time_nhuns = 0;

	Shield::GetInstance()->SetShieldState(new ShieldDownState());
}
PlayerShieldDownState::~PlayerShieldDownState()
{

}

void PlayerShieldDownState::Update(float dt)
{
	
	Player* player = Player::GetInstance();
	player->GetCurrentAnimation()->Update(dt);
	if (player->OnTheWater) {
		this->time_nhuns += dt;
		if (this->time_nhuns >= 0.4f && this->IsNhunsLen) {
			this->time_nhuns = 0;
			this->IsNhunsLen = false;
			player->SetPositionY(player->GetPosition().y + 2);
		}
		if (this->time_nhuns >= 0.4f && this->IsNhunsLen == false) {
			this->time_nhuns = 0;
			this->IsNhunsLen = true;
			player->SetPositionY(player->GetPosition().y - 2);
		}
	}
	
}

void PlayerShieldDownState::Draw()
{

}

void PlayerShieldDownState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	player->time_air_jumping += dt;
	player->time_air_rolling += dt;
	// Xét trường khi đang lót đít trên mật đất
	if (player->IsCollisionWithGround(dt, 18))
	{
		player->SetVelocityY(0);
		// Điều kiện tiên quyết là phải ấn giữ down key, nếu không thì về idle
		if (keyboard->KeyPress(DOWN_KEY)) {
			// Ưu tiên các trạng thái khác
			if (keyboard->KeyPress(LEFT_KEY)) {
				player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
				player->ChangeState(new PlayerRunningState());
				return;
			}
			if (keyboard->KeyPress(RIGHT_KEY)) {
				player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
				player->ChangeState(new PlayerRunningState());
				return;
			}
			if (keyboard->KeyDown(JUMP_KEY)) {
				player->time_air_jumping = 0;
				player->ChangeState(new PlayerJumpingState());
				return;
			}
			// Đặc biệt chuyển qua ngồi đấm chứ không phải đứng đấm
			if (keyboard->KeyDown(ATTACK_KEY)) {
				player->ChangeState(new PlayerDuckingPunchingState());
				return;
			}
		}
		else {
			player->ChangeState(new PlayerIdleState());
			return;
		}
	}
	// Xét trường hợp lướt trên nước
	if (player->IsCollisionWithWater(dt, 16))
	{
		player->SetVelocityY(0);
		player->OnTheWater = true;
		// Xét va chạm 1 lần duy nhất, nếu nhấn giữ thì không có chuyện gì, còn không thì jumping down để
		// về flowing
		if (keyboard->KeyPress(DOWN_KEY)) {
			return;
		}
		else {
			
			player->ChangeState(new PlayerJumpingDownState());
			return;
		}
	}
	// Xét va chạm với mặt nước các lần tiếp theo
	if (player->OnTheWater) {
		// Ưu tiên trạng thái flowing
		if (keyboard->KeyUp(DOWN_KEY) || keyboard->KeyPress(UP_KEY) || keyboard->KeyPress(LEFT_KEY) || 
			keyboard->KeyPress(RIGHT_KEY) || keyboard->KeyDown(ATTACK_KEY)) 
		{
			player->IsShieldDown = false;
			player->ChangeState(new PlayerJumpingDownState());
			return;
		}
		if (keyboard->KeyDown(JUMP_KEY)) {
			player->ChangeState(new PlayerJumpingState());
			return;
		}
	}
	// Xét đang lót đít ở trên không
	if (keyboard->KeyUp(DOWN_KEY)) {
		if (player->time_air_rolling < TIME_ROLLING && player->GetPreviousState() == PlayerState::NameState::rolling) {
			player->ChangeState(new PlayerRollingState());
			return;
		}
		player->ChangeState(new PlayerJumpingDownState());
		return;

	}
	// Di chuyển khi đang lót đít ở trên không
	if (keyboard->KeyPress(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - DELTA_JUMP * dt);
		return;
	}
	if (keyboard->KeyPress(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + DELTA_JUMP * dt);
		return;
	}

	
}
