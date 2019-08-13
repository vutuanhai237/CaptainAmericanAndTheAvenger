#include "Player.h"
#include "PlayerIdleState.h"
#include "PlayerRunningState.h"
#include "PlayerBeatenState.h"
#include "SceneManager.h"
#include "Shield.h"
#include "Framework/DirectInput.h"

Player *Player::instance = NULL;

Player * Player::GetInstance()
{
	if (!instance)
	{
		instance = new Player();
	}
	return instance;
}

void Player::Release()
{
	delete instance;
}

void Player::DrawHP()
{
	int tmp = hp > 20 ? 20 : hp;
	// Position of first HP
	D3DXVECTOR2 pos;
	pos.x = 28;
	pos.y = 20;
	if (hp <= 0)
	{
		return;
	}
	if (hp <= 2)
	{
		if (i >> 3 & 1)
		{
			return;
		}
		HPstatus->SetPosition(pos);
		HPstatus->Draw();
	}
	else
	{
		tmp = (int)ceilf(tmp / 4.0f);
		for (int i = 0; i < tmp; i++)
		{
			HPstatus->SetPosition(pos);
			HPstatus->Draw();
			pos.y += HPstatus->GetInfo()->Height;
		}
	}
}

Player::Player() :Entity()
{
	this->SetTag(Entity::Entity_Tag::player);
	this->SetType(Entity::Entity_Type::player_type);
	this->SetAliveState(Entity::Entity_AliveState::Alive);
	this->SetActive(true);
	// Load resources
	Animation* idle = new Animation(PlayerState::NameState::idle, L"Resources//CaptainState//CaptainIdleState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* running = new Animation(PlayerState::NameState::running, L"Resources//CaptainState//CaptainRunningState.png", D3DCOLOR_XRGB(255, 0, 255), 4);
	Animation* jumping = new Animation(PlayerState::NameState::jumping, L"Resources//CaptainState//CaptainJumpingState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* shield_up = new Animation(PlayerState::NameState::shield_up, L"Resources//CaptainState//CaptainShieldUpState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* dashing = new Animation(PlayerState::NameState::dashing, L"Resources//CaptainState//CaptainDashingState.png", D3DCOLOR_XRGB(255, 0, 255), 3);
	Animation* ducking = new Animation(PlayerState::NameState::ducking, L"Resources//CaptainState//CaptainDuckingState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* throwing = new Animation(PlayerState::NameState::throwing, L"Resources//CaptainState//CaptainThrowingState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* ducking_punching = new Animation(PlayerState::NameState::ducking_punching, L"Resources//CaptainState//CaptainDuckingPunchingState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* rolling = new Animation(PlayerState::NameState::rolling, L"Resources//CaptainState//CaptainRollingState.png", D3DCOLOR_XRGB(255, 0, 255), 4);
	Animation* die = new Animation(PlayerState::NameState::die, L"Resources//CaptainState//CaptainDieState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* diving = new Animation(PlayerState::NameState::diving, L"Resources//CaptainState//CaptainDivingState.png", D3DCOLOR_XRGB(255, 0, 255), 6);
	Animation* flowing = new Animation(PlayerState::NameState::flowing, L"Resources//CaptainState//CaptainFlowingState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* hang_on = new Animation(PlayerState::NameState::hang_on, L"Resources//CaptainState//CaptainHangOnState.png", D3DCOLOR_XRGB(255, 0, 255), 3);
	Animation* jumping_down = new Animation(PlayerState::NameState::jumping_down, L"Resources//CaptainState//CaptainJumpingDownState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* jump_from_rope = new Animation(PlayerState::NameState::jump_from_rope, L"Resources//CaptainState//CaptainJumpingFromRopeState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* kicking = new Animation(PlayerState::NameState::kicking, L"Resources//CaptainState//CaptainKickingState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* punching = new Animation(PlayerState::NameState::punching, L"Resources//CaptainState//CaptainPunchingState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* shield_down = new Animation(PlayerState::NameState::shield_up, L"Resources//CaptainState//CaptainShielDownState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* beaten = new Animation(PlayerState::NameState::beaten, L"Resources//CaptainState//CaptainBeatenState.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* shocking = new Animation(PlayerState::NameState::shocking, L"Resources//CaptainState//CaptainShockingState.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	HPstatus = new Sprite(L"Resources/CaptainState/HP.png", D3DCOLOR_ARGB(0, 0, 0, 0));
	// Chỉ những animation nào có số sprite > 1 thì mới set time
	running->SetTime(0.1f);
	dashing->SetTime(0.05f);
	throwing->SetTime(0.1f);
	ducking_punching->SetTime(0.1f);
	rolling->SetTime(0.03f);
	die->SetTime(0.1f);
	shocking->SetTime(0.032f);
	// diving
	diving->SetTime(0.2f);
	diving->SetFrameReset(4);
	flowing->SetTime(0.1f);
	// hang on
	hang_on->SetTime(0.15f);
	jump_from_rope->SetTime(0.2f);
	punching->SetTime(0.1f);
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
	this->animations[PlayerState::diving] = diving;
	this->animations[PlayerState::flowing] = flowing;
	this->animations[PlayerState::hang_on] = hang_on;
	this->animations[PlayerState::jumping_down] = jumping_down;
	this->animations[PlayerState::jump_from_rope] = jump_from_rope;
	this->animations[PlayerState::kicking] = kicking;
	this->animations[PlayerState::punching] = punching;
	this->animations[PlayerState::shield_down] = shield_down;
	this->animations[PlayerState::beaten] = beaten;
	this->animations[PlayerState::shocking] = shocking;
	// bool
	Entity::IsLocking = true;
	this->IsJumpingDown = false;
	this->IsJumping = false;
	this->IsRolling = false;
	this->IsDuckingPunching = true;
	this->IsDuckingPunching = false;
	this->IsLockCollision = false;
	this->IsShieldDown = false;
	this->IsOnAir = false;
	this->LockState = false;
	this->IsBornSoldier = true;
	this->IsBornRocketRobot = true;
	// time
	this->time_air_jumping = 0;
	this->time_kicking = 0;
	this->time_air_rolling = 0;
	this->time_jumping_before_flowing = 0;
	this->time_don_tho = 0;
	this->time_invisible = 0;
	this->time_guc = 0;
	this->time_buffer = 0;
	// other
	this->animation = this->animations[current_state];
	this->previous_state = 0;
	this->hp = PLAYER_HP;
	this->i = 0;
	this->CarrierObject = NULL;
	this->number_rocket_robot = 0;
	this->number_soldier = 0;
}

Player::~Player()
{
	for (int i = 0; i < 20; i++)
	{
		delete this->animations[i];
	}
}

void Player::Update(float dt)
{
	Entity::Update(dt);
	this->player_state->Update(dt);
	if (this->time_invisible > 0) 
	{
		this->time_invisible -= dt;
	}
}

void Player::Draw()
{
	if (CarrierObject)
	{
		Entity::position.x += CarrierObject->GetVelocityX();
		Entity::position.y += CarrierObject->GetVelocityY();
		if (Shield::GetInstance()->GetShieldState()->GetCurrentState() != ShieldState::NameState::ShieldAttack) 
		{
			Shield::GetInstance()->Update(0);
		}
	}
	i++;
	Player *player = Player::GetInstance();
	Shield *shield = Shield::GetInstance();
	if (player->GetMoveDirection()) 
	{
		player->GetCurrentAnimation()->SetScale(1, 1);
		shield->GetAnimation()->SetScale(1, 1);
	}
	else {

		player->GetCurrentAnimation()->SetScale(-1, 1);
		shield->GetAnimation()->SetScale(-1, 1);
	}
	if (Player::GetInstance()->GetCurrentState() == PlayerState::NameState::shocking) 
	{
		this->animation->Draw(this->position);
		goto CHECK;
	}
	if (this->time_invisible <= 0) 
	{
		this->animation->Draw(this->position);
	}
	else
	{
		if (this->time_invisible <= 0) 
		{
			this->time_invisible = 0;
		}
		if ((i) % 3 == 1)
		{
			this->animation->Draw(this->position);
		}
	}
	CHECK:
	shield->Draw();
	DrawHP();
}

void Player::HandleInput(float dt)
{
	if (DirectInput::GetInstance()->KeyDown(DIK_H))
		this->hp = PLAYER_HP;
	this->player_state->HandleInput(dt);
	IsCollisionWithWall(dt);
}

void Player::Init()
{
	this->player_state = new PlayerIdleState();
}

void Player::ChangeState(PlayerState *new_state)
{
	if (LockState)
	{
		delete new_state;
		return;
	}
	delete this->player_state;
	player_state = new_state;
	this->current_state = player_state->GetCurrentState();
	this->SetCurrentAnimation(this->animations[current_state]);
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
	this->previous_state = this->animation->GetName();
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

int Player::GetPreviousState()
{
	return this->previous_state;
}

int Player::OnCollision(Entity *obj, float dt)
{
	if (obj->GetType() == Entity::Entity_Type::platform && IsCollisionWithPlatform(dt,obj))
	{
		CarrierObject = obj;
	}
	return 0;
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

bool Player::IsCollisionWithGround(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = PLAYER_SIZE_WIDTH;
	FootSize.cy = PLAYER_FOOT_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, velocity.x*dt, velocity.y*dt);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();
	if (foot.vy == 0)
	{
		for (auto item : obj)
		{
			if (item->GetTag() == Entity::Entity_Tag::ground && Checker->IsCollide(foot, BoundingBox(item->GetPosition(), item->GetSize(), 0, 0)))
			{
				return true;
			}
		}
		return false;
	}
	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		if (item->GetTag() == Entity::Entity_Tag::ground)
		{
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(foot, box2);
			if (tmp.side == CollisionSide::bottom)
			{
				position.y = item->GetPosition().y + PLAYER_SIZE_HEIGHT / 2;
				return true;
			}
		}
	}
	return false;
}

bool Player::IsCollisionWithPlatform(float dt, Entity *obj, int delta_y)
{
	if (obj == NULL)
	{
		if (CarrierObject == NULL)
		{
			return false;
		}
		else
		{
			obj = CarrierObject;
		}
	}
	SIZE FootSize;
	FootSize.cx = PLAYER_SIZE_WIDTH;
	FootSize.cy = PLAYER_FOOT_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, velocity.x*dt, velocity.y*dt);
	auto Checker = Collision::getInstance();
	if (abs(foot.vy) == 0.0f && Checker->IsCollide(foot, obj->GetBoundingBox()))
	{
		return true;
	}

	if (Checker->SweptAABB(foot, obj->GetBoundingBox()).side == CollisionSide::bottom)
	{
		position.y = obj->GetPosition().y + (PLAYER_SIZE_HEIGHT + obj->GetSize().cy) / 2 - 4;
		velocity.y = 0;
		return true;
	}	
	return false;
}

bool Player::IsCollisionWithWater(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = PLAYER_SIZE_WIDTH;
	FootSize.cy = PLAYER_FOOT_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, velocity.x*dt, velocity.y*dt);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();
	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		if (item->GetTag() == Entity::Entity_Tag::water)
		{
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(foot, box2);
			if (tmp.side == CollisionSide::bottom)
			{
				return true;
			}
		}
	}
	return false;
}

bool Player::IsCollisionWithWall(float dt, int delta_y)
{
	int ret = 0; 
	Entity::IsLocking = false;
	Entity::Update(dt);
	Entity::IsLocking = true;
	SIZE PlayerSize;
	PlayerSize.cx = PLAYER_SIZE_WIDTH;
	PlayerSize.cy = PLAYER_SIZE_HEIGHT;
	if (current_state == PlayerState::NameState::rolling)
	{
		PlayerSize.cy = PLAYER_SIZE_WIDTH;
	}
	BoundingBox player(D3DXVECTOR2(position.x, position.y - delta_y), PlayerSize, velocity.x*dt, velocity.y*dt);
	Collision *Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();
	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		if (item->GetTag() == Entity::Entity_Tag::wall)
		{
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(player, box2);
			switch (tmp.side)
			{
			case CollisionSide::left:
				if (ret & 1)
				{
					return ret != 0;
				}
				position.x = item->GetPosition().x + (item->GetSize().cx + PLAYER_SIZE_WIDTH) / 2 + 1;
				if (this->GetCurrentState() != PlayerState::NameState::jumping)
				{
					return true;
				}
				ret |= 1;
				break;
			case CollisionSide::right:
				if (ret & 1)
				{
					return ret != 0;
				}
				position.x = item->GetPosition().x - (item->GetSize().cx + PLAYER_SIZE_WIDTH) / 2 - 1;
				if (this->GetCurrentState() != PlayerState::NameState::jumping)
				{
					return true;
				}
				ret |= 1;
				break;
			case CollisionSide::top:
				position.y = item->GetPosition().y - (item->GetSize().cy + PLAYER_SIZE_HEIGHT) / 2;
				velocity.y = 0.0f;
				ret |= 1 << 1;
				break;
			case CollisionSide::bottom:
				if (this->GetCurrentState() == PlayerState::NameState::jumping)
				{
					return false;
				}
				position.y = item->GetPosition().y + (item->GetSize().cy + PLAYER_SIZE_HEIGHT) / 2 - delta_y;				
				velocity.y = 0.0f;
				ret |= 1 << 1;
				break;
			default:
				break;
			}
		}
	}
	return ret != 0;
}

bool Player::IsCollisionWithRope(float dt, int delta_y)
{
	SIZE ArmSize;
	ArmSize.cx = PLAYER_SIZE_WIDTH / 2;
	ArmSize.cy = PLAYER_ARM_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y + delta_y), ArmSize, velocity.x*dt, velocity.y*dt);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();
	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		if (item->GetTag() == Entity::Entity_Tag::rope)
		{
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(foot, box2);
			if (tmp.side == CollisionSide::bottom)
			{
				position.y = item->GetPosition().y - PLAYER_SIZE_HEIGHT / 2 + item->GetSize().cy/2;
				return true;
			}
		}
	}
	return false;
}

bool Player::IsCollisionWithSpike(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = PLAYER_SIZE_WIDTH;
	FootSize.cy = PLAYER_FOOT_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, velocity.x*dt, velocity.y*dt);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();
	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		if (item->GetTag() == Entity::Entity_Tag::spike)
		{
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(foot, box2);
			if (tmp.side == CollisionSide::bottom)
			{
				position.y = item->GetPosition().y + PLAYER_SIZE_HEIGHT / 2;
				return true;
			}
		}
	}
	return false;
}

BoundingBox Player::GetBoundingBox()
{
	return this->player_state->GetBoundingBox();
}