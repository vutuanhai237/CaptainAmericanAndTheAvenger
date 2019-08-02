#include "BossGragas.h"
#include "Shield.h"
#include "ShieldState.h"
#include "PlayerBeatenState.h"
#include "PlayerShockingState.h"
#include "Barrel.h"
#include "SuperLaserBullet.h"
BossGragas*BossGragas::instance = NULL;

BossGragas * BossGragas::GetInstance()
{
	if (!instance)
		instance = new BossGragas();
	return instance;
}

void BossGragas::Release()
{
	delete instance;
}

BossGragas::BossGragas() :Enemy()
{
	///
	this->IsDead = false;
	this->hp = BOSS_GRAGAS_HP;
	this->SetTag(Entity::Entity_Tag::boss);
	this->SetType(Entity::Entity_Type::enemy_type);
	this->SetAliveState(Entity::Entity_AliveState::Alive);
	this->SetActive(true);
	this->SetPosition(220, 200.0f);

	// Load resources
	Animation* idle = new Animation(BossGragas::NameState::idle, L"Resources//Enemy//BossGragas/BossGragasIdle.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* beaten = new Animation(BossGragas::NameState::beaten, L"Resources//Enemy//BossGragas/BossGragasBeaten.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* falling = new Animation(BossGragas::NameState::falling, L"Resources//Enemy//BossGragas/BossGragasFalling.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* firing = new Animation(BossGragas::NameState::firing, L"Resources//Enemy//BossGragas/BossGragasFiring.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	Animation* idle2 = new Animation(BossGragas::NameState::idle2, L"Resources//Enemy//BossGragas/BossGragasIdle2.png", D3DCOLOR_XRGB(255, 0, 255), 1);
	Animation* running = new Animation(BossGragas::NameState::running, L"Resources//Enemy//BossGragas/BossGragasRunning.png", D3DCOLOR_XRGB(255, 0, 255), 3);
	Animation* running2 = new Animation(BossGragas::NameState::running2, L"Resources//Enemy//BossGragas/BossGragasRunning2.png", D3DCOLOR_XRGB(255, 0, 255), 3);
	Animation* throwing = new Animation(BossGragas::NameState::throwing, L"Resources//Enemy//BossGragas/BossGragasThrowing.png", D3DCOLOR_XRGB(255, 0, 255), 2);
	// Chỉ những animation nào có số sprite > 1 thì mới set time
	beaten->SetTime(0.1f);
	running->SetTime(0.1f);
	running2->SetTime(0.1f);
	firing->SetTime(0.5f);
	throwing->SetTime(0.5f);	
	// Cập nhật vào cơ sở dữ liệu
	this->animations[BossGragas::idle] = idle;
	this->animations[BossGragas::beaten] = beaten;
	this->animations[BossGragas::falling] = falling;
	this->animations[BossGragas::firing] = firing;
	this->animations[BossGragas::idle2] = idle2;
	this->animations[BossGragas::running] = running;
	this->animations[BossGragas::running2] = running2;
	this->animations[BossGragas::throwing] = throwing;


	//End load resources
	this->current_state = BossGragas::falling;
	this->animation = this->animations[current_state];
	this->current_animation = this->animations[current_state];
	this->previous_state = 0;
	this->time_invisible = 0;
	this->SetVelocityY(BOSS_GRAGAS_VELOCITY_Y);
	this->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
	this->time_die = 0;
	this->time_idle = 0;
	this->time_throwing = 0;
	this->time_runnig = 0;
	this->mode = Mode::normal;
	this->phase = 1;
	this->time_beaten = 0;
	this->IsBeaten = false;
	this->distance_running = 0;
	this->time_gong = 0;
	this->IsChamDatLanDau = false;
	this->UpdateOneTime = false;
	this->UpdateOneTime2 = false;
	this->IsUpdateRunDirection = false;
	this->run_direction = Entity::Entity_Direction::RightToLeft;
	Entity::size.cx = 20;
	Entity::size.cy = 48;
	this->count_bullet = 0;
	this->j = 0;
}


BossGragas::~BossGragas()
{
	for (int i = 0; i < 8; i++) {
		delete this->animations[i];
	}
}

void BossGragas::Update(float dt)
{
	Enemy::Update(dt);
	this->current_animation->Update(dt);
	if (this->IsExplode) {
		this->time_explode += dt;
		this->current_animation = explode_ani;
		this->SetVelocityX(0.0f);

		if (this->time_explode >= TIME_EXPLODE) {
			this->IsDead = true;
			this->IsActive = false;
			SceneManager::GetInstance()->GetCurrentScene()->IsExitAble = true;

		}
		return;
	}
	BossGragas* boss = BossGragas::GetInstance();
	//if (this->IsBeaten) {
	//	this->current_state = BossGragas::NameState::beaten;
	//	this->current_animation = beaten_ani;
	//	this->SetVelocityX(0.0f);
	//	this->time_beaten += dt;
	//	if (this->time_beaten >= TIME_BEATEN) {
	//		this->IsExplode = true;

	//	}
	//	return;
	//}
	if (boss->time_beaten < 0) {
		boss->time_beaten = 0;
	}
	if (boss->time_beaten > 0) {
		boss->time_beaten -= dt;
	}
	switch (this->mode) {
	case Mode::normal:
		this->UpdateNormalPhase(dt);
		break;
	case Mode::crazy:
		this->UpdateCrazyPhase(dt);
		break;
	}


}

void BossGragas::Draw()
{
	BossGragas* boss = BossGragas::GetInstance();
	if (this->time_beaten == 0) {
		boss->current_animation->Draw(this->position);
	}
	if (this->time_beaten > 0) {	
		if ((j++) % 3 == 1) {
			boss->current_animation->Draw(this->position);
		}
	}

	if (boss->GetMoveDirection()) {
		boss->current_animation->SetScale(1, 1);
	}
	else {
		boss->current_animation->SetScale(-1, 1);
	}
}


CollisionOut BossGragas::IsCollisionWithWall(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = BOSS_GRAGAS_SIZE_WIDTH;
	FootSize.cy = BOSS_GRAGAS_SIZE_HEIGHT;
	int direction_x = BossGragas::GetInstance()->GetMoveDirection() == Entity::Entity_Direction::LeftToRight ? 1 : -1;
	int direction_y = BossGragas::GetInstance()->GetJumpDirection() == Entity::Entity_Jump_Direction::BotToTop ? 1 : -1;

	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, abs(velocity.x*dt)*direction_x, abs(velocity.y)*dt*direction_y);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();

	CollisionOut tmp;
	BoundingBox box2;
	for (auto item : obj)
	{
		if (item->GetTag() == Entity::Entity_Tag::wall)
		{
			box2 = BoundingBox(item->GetPosition(), item->GetSize(), 0, 0);
			tmp = Checker->SweptAABB(foot, box2);
			switch (tmp.side)
			{
			case CollisionSide::bottom:
				if (BossGragas::GetInstance()->GetJumpDirection() == Entity::Entity_Jump_Direction::BotToTop) {
					continue;
				}
				position.y = item->GetPosition().y + (BOSS_GRAGAS_SIZE_HEIGHT + item->GetSize().cy) / 2 - delta_y;
				velocity.y = 0;
				return tmp;
			case CollisionSide::top:
				position.y = item->GetPosition().y - (BOSS_GRAGAS_SIZE_HEIGHT + item->GetSize().cy) / 2 + delta_y - 2;
				velocity.y = 0;
				return tmp;
			case CollisionSide::left:
				position.x = item->GetPosition().x + (BOSS_GRAGAS_SIZE_WIDTH + item->GetSize().cx) / 2 + 2;
				velocity.x = 0;
				return tmp;
			case CollisionSide::right:
				position.x = item->GetPosition().x - (BOSS_GRAGAS_SIZE_WIDTH + item->GetSize().cx) / 2 - 2;
				velocity.x = 0;
				return tmp;
			default:
				continue;
			}
		}
	}
	return tmp;
}

int BossGragas::OnCollision(Entity *obj, float dt)
{
	if (this->IsBeaten == false)
	{
		if (obj->GetType() == Entity::Entity_Type::player_weapon_type
			&& this->mode == Mode::crazy
			&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
		{
			if (this->time_beaten <= 0) {

				if (obj->GetTag() == Entity::Entity_Tag::shield) {
					if (Shield::GetInstance()->GetShieldState()->GetCurrentState() != ShieldState::NameState::Nomal)
					{
						this->hp -= Shield::GetInstance()->GetShieldState()->GetDamage();
						this->time_beaten = ENEMY_TIME_BEATEN;
						goto CHECK;
					}
			
				}
				else {
					// PUNCH - KICH
					this->hp -= 2;
					this->time_beaten = ENEMY_TIME_BEATEN;
					goto CHECK;
				}
			}
		}
		if (this->hp <= 0) {
			this->IsBeaten = true;
			goto CHECK;
		}
	CHECK2:
		Player *player = Player::GetInstance();
		if (obj->GetType() == Entity::Entity_Type::player_type
			&& player->time_invisible <= 0
			&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
		{
			if (BossGragas::GetInstance()->mode == Mode::crazy) {
				player->ChangeState(new PlayerShockingState(BOSS_GRAGAS_DAMAGE*2));

			}
			else {
				player->ChangeState(new PlayerBeatenState(BOSS_GRAGAS_DAMAGE));

			}
		}
		else {
		}

	}
	CHECK:
	if (this->IsDead) {

		return 1;
	}
	return 0;
}

void BossGragas::Init()
{
}

void BossGragas::UpdateNormalPhase(float dt)
{
	BossGragas *boss = BossGragas::GetInstance();
	if (boss->IsChamDatLanDau == false) {
		if (boss->IsCollisionWithWall(dt).CollisionTime < 1.0f) {
			boss->SetVelocityY(0);
			boss->phase++;
			boss->IsChamDatLanDau = true;
		}
	}
	if (boss->count_barrel_explode == 3) {
		boss->mode = Mode::crazy;
		boss->phase = 1;
		return;
	}
	if (boss->phase == 0) {
		boss->current_animation = boss->GetAnimation(NameState::beaten);
		boss->SetCurrentState(NameState::beaten);
		boss->SetVelocity(0, 0);
		this->time_gong += dt;
		if (this->time_gong > BOSS_GRAGAS_TIME_BEATEN) {
			boss->phase = 4;
			this->time_gong = 0;
		}
		return;
	}
	if (boss->phase == 1) {

		return;
	}
	if (boss->phase == 2) {
		if (boss->GetPosition().x > Player::GetInstance()->GetPosition().x) {
			boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		}
		else {
			boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		}
		boss->current_animation = boss->GetAnimation(NameState::idle);
		boss->SetCurrentState(NameState::idle);
		boss->SetVelocity(0, 0);
		boss->time_idle += dt;
		if (boss->time_idle > BOSS_GRAGAS_TIME_IDLE) {
			boss->phase++;
			boss->time_idle = 0;
		}
	}
	if (boss->phase == 3) {
		boss->current_animation = boss->GetAnimation(NameState::throwing);
		boss->current_animation->SetFrame(1);
		boss->SetCurrentState(NameState::throwing);
		boss->time_throwing += dt;
		if (boss->count_bullet == 0)
		{
			SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
				new Barrel(
					D3DXVECTOR2(boss->position.x, boss->position.y + 27),
					this->GetMoveDirection()
				)
			);
			boss->count_bullet++;
		}
		
		if (boss->time_throwing > 1.0f) {
			boss->current_animation->SetFrame(2);
		}
	
		if (boss->time_throwing > BOSS_GRAGAS_TIME_THROWING) {
			boss->phase++;
			boss->count_bullet = 0;
			boss->time_throwing = 0;
		}
	}
	if (boss->phase == 4) {
		boss->current_animation = boss->GetAnimation(NameState::firing);
		boss->SetCurrentState(NameState::firing);
		boss->time_fire += dt;
		if (boss->count_bullet == 0 && boss->time_fire >= 0.6) {
			if (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
				SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
					new SuperLaserBullet(
						D3DXVECTOR2(boss->position.x + 20, this->position.y + 12),
						boss->GetMoveDirection()
					)
				);
			}
			else {
				SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
					new SuperLaserBullet(
						D3DXVECTOR2(boss->position.x - 20, this->position.y + 12),
						boss->GetMoveDirection()
					)
				);
			}
			boss->count_bullet++;
		}
		if (boss->count_bullet == 1 && boss->time_fire >= 1.6) {
			if (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
				SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
					new SuperLaserBullet(
						D3DXVECTOR2(boss->position.x + 20, this->position.y + 12),
						boss->GetMoveDirection()
					)
				);
			}
			else {
				SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
					new SuperLaserBullet(
						D3DXVECTOR2(boss->position.x - 20, this->position.y + 12),
						boss->GetMoveDirection()
					)
				);
			}
			boss->count_bullet++;
		}
		if (boss->time_fire > BOSS_GRAGAS_TIME_FIRING) {
			boss->current_animation->ResetAnimation();
			boss->phase++;
			boss->time_fire = 0;
			boss->count_bullet = 0;
		}
	}
	if (boss->phase == 5) {
		if (boss->UpdateOneTime == false) {
			if (boss->IsUpdateRunDirection == false) goto CHECK;
			if (boss->run_direction == Entity::Entity_Direction::RightToLeft) {
				boss->run_direction = Entity::Entity_Direction::LeftToRight;
				goto CHECK;
			}
			if (boss->run_direction == Entity::Entity_Direction::LeftToRight) {
				boss->run_direction = Entity::Entity_Direction::RightToLeft;
				goto CHECK;
			}
			CHECK:
			boss->current_animation = boss->GetAnimation(NameState::running);
			boss->SetCurrentState(NameState::running);
			boss->SetVelocityX(BOSS_GRAGAS_VELOCITY_X);
			boss->UpdateOneTime = true;
		}
		
		boss->SetMoveDirection(boss->run_direction);
		boss->distance_running += VELOCITY_X * dt;
		if (boss->distance_running > BOSS_GRAGAS_DISTANCE_RUNNING) {
			boss->phase = 2;
			boss->distance_running = 0;
			boss->UpdateOneTime = false;
			boss->IsUpdateRunDirection = true;
		}
	}
	
}

void BossGragas::UpdateCrazyPhase(float dt)
{
	BossGragas *boss = BossGragas::GetInstance();
	if (boss->hp <= 0) {
		boss->phase = 3;
	}
	if (boss->phase == 1) {
		boss->current_animation = boss->GetAnimation(NameState::idle2);
		boss->SetCurrentState(NameState::idle2);
		boss->time_idle += dt;
		if (boss->time_idle >= BOSS_GRAGAS_TIME_IDLE) {
			boss->time_idle = 0;
			boss->phase++;
		}
	}
	if (boss->phase == 2) {
		if (boss->UpdateOneTime == false) {
			if (boss->IsUpdateRunDirection == false) goto CHECK;
			if (boss->run_direction == Entity::Entity_Direction::RightToLeft) {
				boss->run_direction = Entity::Entity_Direction::LeftToRight;
				goto CHECK;
			}
			if (boss->run_direction == Entity::Entity_Direction::LeftToRight) {
				boss->run_direction = Entity::Entity_Direction::RightToLeft;
				goto CHECK;
			}
			CHECK:
			boss->current_animation = boss->GetAnimation(NameState::running2);
			boss->SetCurrentState(NameState::running2);
			boss->SetVelocityX(BOSS_GRAGAS_VELOCITY_X);
			boss->UpdateOneTime = true;
		}

		boss->SetMoveDirection(boss->run_direction);
		boss->distance_running += VELOCITY_X * dt;
		boss->time_fire += dt;
		if (boss->time_fire > 1) {
			if (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
				SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
					new SuperLaserBullet(
						D3DXVECTOR2(boss->position.x + 20, this->position.y + 12),
						boss->GetMoveDirection()
					)
				);
			}
			else {
				SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
					new SuperLaserBullet(
						D3DXVECTOR2(boss->position.x - 20, this->position.y + 12),
						boss->GetMoveDirection()
					)
				);
			}
			boss->time_fire = 0;
		}
		if (boss->distance_running > BOSS_GRAGAS_DISTANCE_RUNNING) {
			boss->phase = 2;
			boss->distance_running = 0;
			boss->UpdateOneTime = false;
		}
	}
	if (boss->phase == 3) {
		if (this->UpdateOneTime2 == false) {
			boss->current_animation = boss->GetAnimation(NameState::idle2);
			boss->SetCurrentState(NameState::idle2);
			boss->SetVelocity(0, 0);
		}
		if ((j) % 6 == 3 || (j) % 6 == 2 || (j) % 6 == 4) {
			boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		}
		else {
			boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		}
		j++;
		boss->time_idle += dt;
		if (boss->time_idle >= BOSS_GRAGAS_TIME_IDLE_BEFORE_DIE) {
			boss->time_idle = 0;
			boss->IsExplode = true;
		}
	}
}

BossGragas::NameState BossGragas::GetCurrentState()
{
	return this->current_state;
}

void BossGragas::SetCurrentState(BossGragas::NameState new_state)
{
	this->current_state = new_state;
}


void BossGragas::SetCurrentAnimation(Animation * animation)
{
	this->current_animation = animation;
}

Animation * BossGragas::GetCurrentAnimation()
{
	return this->animation;
}

Animation * BossGragas::GetAnimation(BossGragas::NameState state)
{
	return this->animations[state];
}

int BossGragas::GetPreviousState()
{
	return this->previous_state;
}