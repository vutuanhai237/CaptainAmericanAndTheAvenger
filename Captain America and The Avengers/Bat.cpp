#include "Bat.h"
#include "Shield.h"
#include "FrameWork/SoundManager.h"
#include "PlayerShockingState.h"
#include "PlayerBeatenState.h"

void Bat::Update(float dt)
{
	Enemy::Update(dt);
	this->current_animation->Update(dt);

	if (this->level == Level::electric && (this->position.x - Player::GetInstance()->GetPosition().x) < 50) {
		this->active = true;
	}

	if (this->level == Level::normal && this->hp == 1) {
		this->active = true;
	}

	if (this->IsCollisionWithSpike(dt)) {
		this->hp = 0;
	}
	
	if (this->IsExplode) {
		this->time_explode += dt;
		this->current_animation = this->explode_ani;
		this->SetVelocity(0, 0);
		if (this->time_explode >= TIME_EXPLODE) {
			this->IsDead = true;
			this->IsActive = false;
		}
		return;
	}

	if (this->IsBeaten) {
		this->current_animation = beaten_ani;
		this->SetVelocity(0, BAT_VELOCITY_Y);
		this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
		if (this->IsCollisionWithGround(dt)) {
			this->IsExplode = true;	
			SoundManager::GetInstance()->Play(SoundManager::SoundList::entity_explode);
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
	if (phase == 0) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->SetVelocity(0, 0);
			this->UpdateOneTime = true;
		}
		this->time_idle += dt;
		if (time_idle > BAT_TIME_IDLE) {
			this->time_idle = 0;
			this->phase = 2;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 1) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->idle_ani;
			this->current_animation->Stop();
			this->SetVelocity(0, 0);
			this->UpdateOneTime = true;
		}
		if (this->active) {
			this->current_animation->Continue();
			if (this->UpdateOneTime2 == false) {
				this->current_animation->ResetAnimation();
				this->UpdateOneTime2 = true;
			}
		}
		else return;
		this->time_idle += dt;
		if (time_idle > BAT_TIME_IDLE) {
			this->time_idle = 0;
			this->phase++;
			this->UpdateOneTime = false;
			this->UpdateOneTime2 = false;

		}
	}

	if (phase == 2) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_2_12) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 3) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_3_11 + 20) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 4) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_4_10 - 20) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 5) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_5_7_9 + 40) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 6) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->IsVoDich = false;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_6_8 - 10) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 7) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_5_7_9 + 40) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 8) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_6_8 - 10) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 9) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_5_7_9 + 40) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 10) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_4_10 - 20) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 11) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_3_11 + 20) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 12) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->position.y >= this->position_spawn.y 
			|| this->distance > BAT_DISTANCE_PHASE_2_12) {
			this->distance = 0;
			this->phase++;
			this->position = this->position_spawn;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 13) {
		phase = 0;
	}
}

void Bat::UpdateElectricLevel(float dt)
{
	if (phase == 1) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->idle2_ani;
			this->current_animation->Stop();
			this->SetVelocity(0, 0);
			this->UpdateOneTime = true;
		}
		if (this->active) {
			this->current_animation->Continue();
			if (this->UpdateOneTime2 == false) {
				this->current_animation->ResetAnimation();
				this->UpdateOneTime2 = true;
			}		
		}
		else {
			return;
		}
		this->time_idle += dt;
		if (this->time_idle > BAT_TIME_IDLE) {
			this->time_idle = 0;
			this->phase++;
			this->UpdateOneTime = false;
			this->UpdateOneTime2 = false;
		}
	}

	if (phase == 2) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->IsVoDich = true;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_2_12) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 3) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->IsVoDich = true;
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

	if (phase == 4) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->IsVoDich = true;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_4_10) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}
	if (phase == 5) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->IsVoDich = true;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_5_7_9) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}
	if (phase == 6) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->IsVoDich = false;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_6_8) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 7) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying_ani;
			this->IsVoDich = false;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_X * dt;
		if (this->distance > BAT_DISTANCE_PHASE_5_7_9) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 8) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->IsVoDich = true;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->distance > BAT_DISTANCE_PHASE_6_8) {
			this->distance = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 9) {
		if (this->UpdateOneTime == false) {
			this->current_animation = this->flying2_ani;
			this->IsVoDich = true;
			this->SetVelocity(BAT_VELOCITY_X, 0);
			this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
			this->UpdateOneTime = true;
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
			this->IsVoDich = true;
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
			this->IsVoDich = true;
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
			this->current_animation = this->flying_ani;
			this->IsVoDich = false;
			this->SetVelocity(0, BAT_VELOCITY_Y);
			this->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
			this->UpdateOneTime = true;
		}
		this->distance += BAT_VELOCITY_Y * dt;
		if (this->position.y >= this->position_spawn.y || this->distance > BAT_DISTANCE_PHASE_2_12) {
			this->distance = 0;
			this->phase++;
			this->position.y = this->position_spawn.y;
			this->UpdateOneTime = false;
		}
	}

	if (phase == 13) {
		phase = 1;
	}
}

int Bat::OnCollision(Entity* obj, float dt)
{
	if (this->IsBeaten == false)
	{
		if (obj->GetType() == Entity::Entity_Type::player_weapon_type
			&& this->IsVoDich == false
			&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
		{	
			if (this->time_beaten == 0) {
				this->hp--;
				this->time_beaten = ENEMY_TIME_BEATEN;
			}
		}

		if (this->hp <= 0) {
			this->IsBeaten = true;
			goto CHECK;
		}
		Player *player = Player::GetInstance();
		if (obj->GetType() == Entity::Entity_Type::player_type
			&& player->GetCurrentState() != PlayerState::shield_down
			&& player->time_invisible <= 0
			&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
		{
			if (this->time_beaten == 0) {
				if (this->IsVoDich == false) { this->hp--; this->time_beaten = ENEMY_TIME_BEATEN; }
				if (this->level == Level::normal) {
					player->ChangeState(new PlayerBeatenState(BAT_DAMAGE));
				}
				else {
					if (this->phase == 1) {
						if (this->IsVoDich == false) this->hp--;
						player->ChangeState(new PlayerBeatenState(BAT_DAMAGE));
					}
					else {
						player->ChangeState(new PlayerShockingState(BAT_DAMAGE));

					}
				}
			}
		}
		if (this->hp <= 0) {
			this->IsBeaten = true;
		}
	}
	CHECK:
	if (this->IsDead) {

		return 1;
	}
	return 0;
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
			if (Checker->IsCollide(foot, BoundingBox(item->GetPosition(), item->GetSize(), 0, 0)))
				return true;
		}
		return false;
	}
	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
		tmp = Checker->SweptAABB(foot, box2);
		if (tmp.side == CollisionSide::bottom)
		{
			return true;
		}
		if (tmp.side == CollisionSide::top)
		{
			return true;
		}
	}
	return false;
}

bool Bat::IsCollisionWithSpike(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = BAT_SIZE_WIDTH;
	FootSize.cy = BAT_FOOT_HEIGHT;
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
	this->explode_ani = new Animation(7, 3);
	this->beaten_ani = new Animation(BatState::flying, 2);
	// set animation zone
	this->idle_ani->SetTime(0.3f);
	this->idle2_ani->SetTime(0.3f);
	this->flying_ani->SetTime(0.1f);
	this->flying2_ani->SetTime(0.1f);
	this->explode_ani->SetTime(0.083f, 10000.0f);
	this->beaten_ani->SetFrame(2); this->beaten_ani->Stop();
	// set properties zone
	this->position = position_spawn;
	this->position_spawn = position_spawn;
	this->current_animation = idle_ani;
	this->i = 0;
	this->hp = BAT_HP;
	if (direction == 0) {
		this->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
	}
	else {
		this->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
	}
	this->distance = 0;
	this->time_idle = 0;
	this->phase = 1;
	// flag zone
	this->active = false;
	this->UpdateOneTime = false;
	this->IsVoDich = false;
	this->UpdateOneTime2 = false;
	// handle follow level zone
	switch (level) {
	case 0:
		this->level = Level::normal;
		break;
	case 1:
		this->level = Level::electric;
		break;
	}
}

Bat::~Bat()
{

}