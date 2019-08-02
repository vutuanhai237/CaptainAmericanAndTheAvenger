#include "Turret.h"
#include "Shield.h"
#include "Player.h"
#include "PlayerBeatenState.h"
#include "TurretBullet.h"

void Turret::Update(float dt)
{
	Enemy::Update(dt);
	this->current_animation->Update(dt);
	if (this->IsExplode) {
		this->time_explode += dt;
		this->current_animation = explode_ani;
		if (this->time_explode >= TIME_EXPLODE) {
			this->IsDead = true;
			this->IsActive = false;
		}
		return;
	}

	switch (this->current_state) {
	case NameState::rolling:
		this->UpdateRollingState(dt);
		break;
	case NameState::firing:
		this->UpdateFiringState(dt);
		break;
	}
}


int Turret::OnCollision(Entity* obj, float dt)
{
	if (this->current_state == NameState::firing)
	{
		if (obj->GetType() == Entity::Entity_Type::player_weapon_type
			&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
		{
			if (obj->GetTag() == Entity::Entity_Tag::shield) {
				if (Shield::GetInstance()->GetShieldState()->GetCurrentState() == ShieldState::NameState::ShieldAttack)
				{
					this->current_state = NameState::rolling;
					this->hp--;
				}
			}
			else {
				this->current_state = NameState::rolling;
				this->hp--;
			}
		}
		if (this->hp <= 0) {
			this->IsBeaten = true;
			this->IsExplode = true;
			goto CHECK;
		}
		Player *player = Player::GetInstance();
		if (obj->GetType() == Entity::Entity_Type::player_type
			&& player->time_invisible <= 0
			&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
		{
			this->current_state = NameState::rolling;
			this->hp--;
			player->ChangeState(new PlayerBeatenState(ENEMY_DAMAGE));
		}

		if (this->hp <= 0) {
			this->IsBeaten = true;
			this->IsExplode = true;
		}
	}
	CHECK:
	if (this->IsDead) {
		return 1;
	}
	return 0;
}

void Turret::Draw()
{
	this->current_animation->SetRotation((int)alpha);
	this->current_animation->DrawInt(this->position);
CHECK:
	if (this->GetMoveDirection()) {
		this->GetCurrentAnimation()->SetScale(1, 1);
	}
	else {
		this->GetCurrentAnimation()->SetScale(-1, 1);
	}
}

BoundingBox Turret::GetBoundingBox()
{
	SIZE size;
	size.cx = 16;
	size.cy = 16;
	return BoundingBox(Entity::position, size, Entity::velocity.x, Entity::velocity.y);
}

void Turret::UpdateRollingState(float dt)
{
	frame++;
	if (frame == 50) {
		this->current_state = NameState::firing;
		this->time_rolling = 0;
		frame = 0;
		return;
	}
	this->alpha -= this->omega;
}

void Turret::UpdateFiringState(float dt)
{
	this->time_fire += dt;
	if (this->time_fire > TURRET_TIME_FIRING) {
		if (this->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
			SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
				new TurretBullet(
					D3DXVECTOR2(this->position.x, this->position.y),
					this->GetMoveDirection(),
					this->alpha
				)
			);
		}
		else {
			SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
				new TurretBullet(
					D3DXVECTOR2(this->position.x, this->position.y),
					this->GetMoveDirection(),
					this->alpha
				)
			);
		}
		this->time_fire = 0;
	}
}

Turret::Turret(D3DXVECTOR2 position_spawn, float alpha) : Enemy()
{
	// init animation zone
	this->SetTag(Entity::Entity_Tag::cannon);
	this->SetType(Entity::Entity_Type::enemy_type);
	this->current_animation = new Animation(30, 1);
	this->current_animation->SetTime(0.5);
	this->position = position_spawn;
	this->explode_ani = new Animation(7, 3);
	this->explode_ani->SetTime(0.083, 10000);
	this->time_explode = 0;
	this->size.cx = 16;
	this->size.cy = 16;
	this->SetVelocity(0, 0);
	this->time_fire = 0;
	this->alpha = alpha;
	this->omega = 45;
	this->IsBeaten = false;
	this->frame = 0;
	this->current_state = NameState::firing;
	this->time_rolling = 0;
	this->hp = TURRET_HP;
}

Turret::~Turret()
{
}

