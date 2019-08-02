#include "Bat.h"
#include "Shield.h"
#include "FrameWork//Debug.h"

void Bat::Update(float dt)
{
	Enemy::Update(dt);
	this->current_animation->Update(dt);
	if (abs(this->position.x - Player::GetInstance()->GetPosition().x) < 50) this->active = true;

	if (this->IsExplode) {
		this->time_explode += dt;
		this->current_animation = explode_ani;
		this->SetVelocityX(0.0f);

		if (this->time_explode >= TIME_EXPLODE) {
			this->IsDead = true;
			this->IsActive = false;
		}
		return;
	}
	if (this->IsBeaten) {
		this->current_animation = beaten_ani;
		this->SetVelocityX(0.0f);
		this->time_beaten += dt;
		if (this->time_beaten >= TIME_BEATEN) {
			this->IsExplode = true;

		}
		if (this->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
			this->position.x -= 1;

		}
		else {
			this->position.x += 1;
		}
		return;
	}

	switch (this->level) {
	case Level::electric:
		this->UpdateElectricLevel(dt);
		break;
	case Level::normal:
		this->UpdateNormalLevel(dt);
		break;
	}
}

void Bat::UpdateNormalLevel(float dt)
{
	
}

void Bat::UpdateElectricLevel(float dt)
{
	if (phase == 1) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->idle2_ani;
			this->current_animation->SetFrame(1);
			this->current_animation->Stop();
			this->SetVelocity(0, 0);
			this->UpdateOneTime == true;
		}
		if (this->active) {
			this->current_animation->Continue();
		}
		else return;
		this->time_idle += dt;
		if (time_idle > BAT_TIME_IDLE) {
			this->time_idle = 0;
			this->phase++;
			this->UpdateOneTime == false;
		}
	}
	if (phase == 2) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
			this->UpdateOneTime == true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_2_12) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime == false;
		}
	}
	if (phase == 3) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			this->UpdateOneTime == true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_3_11) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime == false;
		}
	}
	if (phase == 4) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
			this->UpdateOneTime == true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_4_10) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime == false;
		}
	}
	if (phase == 5) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
			this->UpdateOneTime == true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_5_7_9) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime == false;
		}
	}
	if (phase == 6) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
			this->UpdateOneTime == true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_6_8) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime == false;
		}
	}
	if (phase == 7) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			this->UpdateOneTime == true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_5_7_9) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime == false;
		}
	}
	if (phase == 8) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
			this->UpdateOneTime == true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_6_8) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime == false;
		}
	}
	if (phase == 9) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
			this->UpdateOneTime == true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_5_7_9) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}
	if (phase == 10) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_4_10) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}
	if (phase == 11) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_3_11) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}
	if (phase == 12) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_2_12) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}
}

int Bat::OnCollision(Entity* obj, float dt)
{
	return Enemy::OnCollision(obj, dt);
}

void Bat::Draw()
{
	Enemy::Draw();
}

BoundingBox Bat::GetBoundingBox()
{
	SIZE size;
	size.cx = 16;
	size.cy = 16;
	return BoundingBox(Entity::position, size, Entity::velocity.x, Entity::velocity.y);
}

bool Bat::IsCollisionWithGround(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = BAT_SIZE_WIDTH;
	FootSize.cy = BAT_FOOT_HEIGHT;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, velocity.x*dt, velocity.y*dt);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();

	if (foot.vy == 0)
	{
		for (auto item : obj)
		{
			if (item->GetTag() == Entity::Entity_Tag::ground && Checker->IsCollide(foot, BoundingBox(item->GetPosition(), item->GetSize(), 0, 0)))
				return true;
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
				position.y = item->GetPosition().y + BAT_SIZE_HEIGHT / 2;
				return true;
			}
		}
	}
	return false;
}

Bat::Bat(int level, D3DXVECTOR2 position_spawn) : Enemy()
{
	// init animation zone
	this->SetTag(Entity::Entity_Tag::bat);
	this->SetType(Entity::Entity_Type::enemy_type);
	this->idle_ani = new Animation(BatState::idle, 3);
	this->idle2_ani = new Animation(BatState::idle2, 3);
	this->flying_ani = new Animation(BatState::flying, 2);
	this->flying2_ani = new Animation(BatState::flying2, 2);
	// set animation zone
	this->idle_ani->SetTime(0.1);
	this->idle2_ani->SetTime(0.1);
	this->flying_ani->SetTime(0.1);
	this->flying2_ani->SetTime(0.1);
	// set properties zone
	this->position = position_spawn;
	this->current_animation = idle_ani;
	this->hp = BAT_HP;
	if (direction == 0) {
		this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
	}
	else {
		this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
	}
	this->distance = 0;
	// time zone
	this->time_idle = 0;
	// flag zone
	this->active = false;
	this->UpdateOneTime = false;
	// handle follow level zone
	switch (level) {
	case 0:
		this->level = Level::normal;
		break;
	case 1:
		this->level = Level::electric;
		break;
	}
	switch (this->level) {
	case Level::normal:
		//this->IsIdle = true;
		//this->current_state = BatState::idle;
		//this->current_animation = idle_ani;
		//this->SetVelocityX(0.0f);
		this->phase = 1;
		break;
	case Level::electric:
		//this->current_state = BatState::running;
		//this->current_animation = running_ani;
		//this->SetVelocityX(BAT_VELOCITY_X);
		this->phase = 1;
		break;
	}
}

Bat::~Bat()
{
}

