#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerRunningState.h"
#include "SceneManager.h"
#include "../Map/Framework/Debug.h"
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
	this->time_buffer = 0;
	this->SetTag(Entity::Entity_Tag::player);
	this->SetType(Entity::Entity_Type::player_type);
	this->SetAliveState(Entity::Entity_AliveState::Alive);
	this->SetActive(true);
	/// Load resources
	Animation* idle = new Animation(PlayerState::NameState::idle, L"Resources//CaptainState//CaptainIdleState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* running = new Animation(PlayerState::NameState::running, L"Resources//CaptainState//CaptainRunningState.png", D3DCOLOR_XRGB(255, 0, 255), 4);
	Animation* jumping = new Animation(PlayerState::NameState::jumping, L"Resources//CaptainState//CaptainJumpingState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* shield_up = new Animation(PlayerState::NameState::shield_up, L"Resources//CaptainState//CaptainShieldUpState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* dashing = new Animation(PlayerState::NameState::dashing, L"Resources//CaptainState//CaptainDashingState.png", D3DCOLOR_XRGB(255, 0, 255), 3);
	Animation* ducking = new Animation(PlayerState::NameState::ducking, L"Resources//CaptainState//CaptainDuckingState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* throwing = new Animation(PlayerState::NameState::throwing, L"Resources//CaptainState//CaptainThrowingState.png", D3DCOLOR_XRGB(255, 0, 255), 2);

	Animation* ducking_punching = new Animation(PlayerState::NameState::ducking_punching, L"Resources//CaptainState//CaptainDuckingPunchingState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* rolling = new Animation(PlayerState::NameState::rolling,L"Resources//CaptainState//CaptainRollingState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* die = new Animation(PlayerState::NameState::die, L"Resources//CaptainState//CaptainDieState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* die_on_air = new Animation(PlayerState::NameState::die_on_air, L"Resources//CaptainState//CaptainDieOnAirState.png", D3DCOLOR_XRGB(255, 0, 255), 3);
	Animation* diving = new Animation(PlayerState::NameState::diving, L"Resources//CaptainState//CaptainDivingState.png", D3DCOLOR_XRGB(255, 0, 255), 6);
	Animation* flowing = new Animation(PlayerState::NameState::flowing, L"Resources//CaptainState//CaptainFlowingState.png", D3DCOLOR_XRGB(255, 0, 255), 9);
	Animation* hang_on = new Animation(PlayerState::NameState::hang_on, L"Resources//CaptainState//CaptainHangOnState.png", D3DCOLOR_XRGB(255, 0, 255), 3);
	Animation* jumping_down = new Animation(PlayerState::NameState::jumping_down, L"Resources//CaptainState//CaptainJumpingDownState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* jump_from_rope = new Animation(PlayerState::NameState::jump_from_rope, L"Resources//CaptainState//CaptainJumpingFromRopeState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* kicking = new Animation(PlayerState::NameState::kicking, L"Resources//CaptainState//CaptainKickingState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* punching = new Animation(PlayerState::NameState::punching, L"Resources//CaptainState//CaptainPunchingState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* shield_down = new Animation(PlayerState::NameState::shield_up, L"Resources//CaptainState//CaptainShielDownState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	// Chỉ những animation nào có số sprite > 1 thì mới set time
	running->SetTime(0.1);
	dashing->SetTime(0.1);
	throwing->SetTime(0.1);
	ducking_punching->SetTime(0.1);
	rolling->SetTime(0.1);
	die->SetTime(0.1);
	die_on_air->SetTime(0.1);
	diving->SetTime(0.1);
	flowing->SetTime(0.1);
	hang_on->SetTime(0.1);
	jump_from_rope->SetTime(0.1);
	punching->SetTime(0.1);

	// Cập nhật vào cơ sở dữ liệu
	this->animations[PlayerState::idle] = idle;
	this->animations[PlayerState::running] = running;
	this->animations[PlayerState::jumping] = jumping;
	this->animations[PlayerState::shield_up] = shield_up;
	this->animations[PlayerState::dashing] = dashing;
	this->animations[PlayerState::ducking] = ducking;
	this->animations[PlayerState::throwing] = throwing;
	this->animations[PlayerState::ducking_punching] = ducking_punching;
	this->animations[PlayerState::rolling] = rolling;
	this->animations[PlayerState::die] = die;
	this->animations[PlayerState::die_on_air] = die_on_air;
	this->animations[PlayerState::diving] = diving;
	this->animations[PlayerState::flowing] = flowing;
	this->animations[PlayerState::hang_on] = hang_on;
	this->animations[PlayerState::jumping_down] = jumping_down;
	this->animations[PlayerState::jump_from_rope] = jump_from_rope;
	this->animations[PlayerState::kicking] = kicking;
	this->animations[PlayerState::punching] = punching;
	this->animations[PlayerState::shield_down] = shield_down;

	///End load resources
	this->animation = this->animations[current_state];



	// Cập nhật trạng thái rolling hay diving
	this->IsRolling = false;
	this->IsDuckingPunching = true;
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
	//Debug::PrintOut(L"x = %f, y = %f\n", this->position.x, this->position.y);
}

void Player::HandleInput(float dt)
{
	this->player_state->HandleInput(dt);
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

void Player::SetCurrentAnimation(Animation * animation)
{
	this->animation = animation;
}

Animation * Player::GetCurrentAnimation()
{
	return this->animation;
}

Animation * Player::GetAnimation(PlayerState::NameState state)
{
	return this->animations[state];
}

void Player::SetPosition(float x, float y)
{
	Entity::SetPosition(x, y);
	this->animation->SetPosition(x, y);
}

void Player::AddTimeBuffer(float dt)
{
	this->time_buffer += dt;
}

float Player::GetTimeBuffer()
{
	return this->time_buffer;
}

void Player::SetTimeBuffer(float dt)
{
	this->time_buffer = dt;
}

void Player::SetIsRolling(bool IsRolling)
{
	this->IsRolling = IsRolling;
}

bool Player::GetIsRolling()
{
	return this->IsRolling;
}

void Player::SetIsThrowing(bool IsThrowing)
{
	this->IsThrowing = IsThrowing;
}

bool Player::GetIsThrowing()
{
	return this->IsThrowing;
}

void Player::SetPositionIdle(D3DXVECTOR2 position_idle)
{
	this->position_idle = position_idle;
}



D3DXVECTOR2 Player::GetPositionIdle()
{
	return this->position_idle;
}

void Player::SetIsDuckingPunching(bool IsDuckingpunching)
{
	this->IsDuckingPunching = IsDuckingPunching;
}

bool Player::GetIsDuckingPunching()
{
	return this->IsDuckingPunching;
}

bool Player::IsCollisionWithGround(float dt)
{
	SIZE FootSize;
	FootSize.cx = PLAYER_SIZE_WIDTH;
	FootSize.cy = PLAYER_FOOT_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - 17), FootSize, velocity.x*dt, velocity.y*dt);
	foot.vy = foot.vy > 0 ? foot.vy : -2;
	auto Checker = Collision::getInstance();

	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();

	CollisionOut tmp;
	for (auto item : obj)
	{
		BoundingBox box2;
		switch (item->GetTag())
		{
		case Entity::Entity_Tag::ground:
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(foot, box2);
			if (tmp.side == CollisionSide::bottom || tmp.side == CollisionSide::top)
			{
				position.y = item->GetPosition().y + PLAYER_SIZE_HEIGHT / 2 - 4;
				return true;
			}
			break;
		default:
			break;
		}
	}
	return false;
}