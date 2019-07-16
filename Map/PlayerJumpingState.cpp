#include "PlayerJumpingState.h"
#include "PlayerIdleState.h"

#include "Framework//Debug.h"
PlayerJumpingState::PlayerJumpingState()
{
	Player* player = Player::GetInstance();
	player->SetCurrentState(PlayerState::NameState::jumping);
	this->current_state = PlayerState::NameState::jumping;
	player->SetVelocityY(VELOCITY_Y);
	player->SetIsOnAir(true);
	player->SetTimeBuffer(0);

}
PlayerJumpingState::~PlayerJumpingState()
{

}

void PlayerJumpingState::Update(float dt)
{
	Player* player = Player::GetInstance();

	player->GetCurrentAnimation()->Update(dt);
	float new_y = player->GetPosition().y;
	float velocity_y = player->GetVelocity().y;
	if (player->GetPosition().y >= 100.0f) {
		player->SetVelocityY(-abs(velocity_y));
	}
	player->SetPosition(player->GetPosition().x, new_y + dt * velocity_y);
	//Debug::PrintOut(L"y = %f\n", player->GetPosition().y);
}

void PlayerJumpingState::Draw()
{

}

void PlayerJumpingState::Render()
{
}

void PlayerJumpingState::HandleInput(float dt)
{
	Player* player = Player::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	// Đang ở trên không, nếu ấn left thì dịch qua trái
	if (keyboard->KeyPress(LEFT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		player->SetPositionX(player->GetPosition().x - 0.5f);
		//return;
	}
	// Đang ở trên không, nếu ấn left thì dịch qua phải
	if (keyboard->KeyPress(RIGHT_KEY)) {
		player->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		player->SetPositionX(player->GetPosition().x + 0.5f);
		//return;
	}
	// Code xong va chạm thì xóa hàm này với bỏ comment return chỗ left & right
	if (player->GetPosition().y <= 50.0f) {
		player->ChangeState(new PlayerIdleState());
		return;
	}
	
}
