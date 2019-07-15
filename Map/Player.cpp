#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerRunningState.h"

Player*Player::instance = NULL;

Player * Player::GetInstance()
{
	if (!instance) 
		instance = new Player();
	return instance;
}

Player::Player() :Entity()
{
	///
	this->SetTag(Entity::Entity_Tag::player);
	this->SetType(Entity::Entity_Type::player_type);
	this->SetAliveState(Entity::Entity_AliveState::Alive);
	this->SetActive(true);
	/// Load resources
	Animation* idle = new Animation(L"Resources//CaptainState//CaptainIdleState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* running = new Animation(L"Resources//CaptainState//CaptainRunningState.png", D3DCOLOR_XRGB(255, 0, 255), 4);
	Animation* jumping = new Animation(L"Resources//CaptainState//CaptainJumpingState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	
	
	running->SetTime(0.3);

	this->animations[PlayerState::idle] = idle;
	this->animations[PlayerState::running] = running;
	this->animations[PlayerState::jumping] = jumping;
	///End load resources
	this->animation = this->animations[current_state];
	
}


Player::~Player()
{
}

void Player::Update(float dt)
{
	Entity::Update(dt);

	this->player_state->Update(dt);
}

void Player::Render()
{
	this->player_state->Render();
}

void Player::Draw()
{
	this->animation->Draw(this->position);
	
}

void Player::HandleInput()
{
	this->player_state->HandleInput();
}

void Player::Init()
{
	this->player_state = new PlayerIdleState();
	
}

void Player::ChangeState(PlayerState *new_state)
{
	delete this->player_state;
	player_state = new_state;
	this->current_state = player_state->GetCurrentState();
	this->animation = this->animations[current_state];

}

PlayerState::NameState Player::GetCurrentState()
{
	return this->current_state;
}

PlayerState * Player::GetPlayerState()
{
	return this->player_state;
}

void Player::SetCurrentState(PlayerState::NameState new_state)
{
	this->current_state = new_state;
}

Animation * Player::GetCurrentAnimation()
{
	return this->animation;
}

void Player::SetPosition(float x, float y)
{
	Entity::SetPosition(x, y);
	this->animation->SetPosition(x, y);
}
