#include "BossWizard.h"
#include "BossWizardFlyingState.h"
#include "BossWizardUMaxRoad.h"
#include "BossWizardIdleRoad.h"
#include "BossWizardBeatenRoad.h"
#include "Shield.h"
#include "ShieldState.h"
#include "PlayerBeatenState.h"
#include "Framework/SoundManager.h"
BossWizard*BossWizard::instance = NULL;

BossWizard * BossWizard::GetInstance()
{
	if (!instance)
		instance = new BossWizard();
	return instance;
}

void BossWizard::Release()
{
	if (instance)
		delete instance;
	this->instance = NULL;
}

BossWizard::BossWizard() :Enemy()
{
	///
	this->IsDead = false;
	this->hp = BOSS_WIZARD_HP;
	this->time_buffer = 0;
	this->SetTag(Entity::Entity_Tag::boss);
	this->SetType(Entity::Entity_Type::enemy_type);
	this->SetAliveState(Entity::Entity_AliveState::Alive);
	this->SetActive(true);
	// Load resources
	Animation* idle = new Animation(BossWizardState::NameState::idle, L"Resources//Enemy//BossWizard/BossWinzardIdle.png", D3DCOLOR_XRGB(0, 166, 81), 3);
	Animation* running = new Animation(BossWizardState::NameState::running, L"Resources//Enemy//BossWizard/BossWizardRunning.png", D3DCOLOR_XRGB(0, 166, 81), 4);
	Animation* flying = new Animation(BossWizardState::NameState::flying, L"Resources//Enemy//BossWizard/BossWizardFlying.png", D3DCOLOR_XRGB(0, 166, 81), 2);
	Animation* fire = new Animation(BossWizardState::NameState::fire, L"Resources//Enemy//BossWizard/BossWizardFire.png", D3DCOLOR_XRGB(0, 166, 81), 3);
	Animation* flying_fire = new Animation(BossWizardState::NameState::flying_fire, L"Resources//Enemy//BossWizard/BossWizardFlyingFire.png", D3DCOLOR_XRGB(0, 166, 81), 1);
	Animation* punching = new Animation(BossWizardState::NameState::punching, L"Resources//Enemy//BossWizard/BossWizardPunching.png", D3DCOLOR_XRGB(0, 166, 81), 2);
	Animation* punching_fire = new Animation(BossWizardState::NameState::punching_fire, L"Resources//Enemy//BossWizard/BossWizardPunchingFire.png", D3DCOLOR_XRGB(0, 166, 81), 2);
	Animation* beaten = new Animation(BossWizardState::NameState::beaten, L"Resources//Enemy//BossWizard/BossWizardBeaten.png", D3DCOLOR_XRGB(0, 166, 81), 1);
	Animation* die = new Animation(BossWizardState::NameState::die, L"Resources//Enemy//BossWizard/BossWizardDie.png", D3DCOLOR_XRGB(0, 166, 81), 2);
	// Chỉ những animation nào có số sprite > 1 thì mới set time
	running->SetTime(0.1f);
	idle->SetTime(0.2f); idle->SetFrameReset(2);
	fire->SetTime(0.1f);
	flying->SetTime(1000000.0f);
	punching->SetTime(0.1f);
	punching_fire->SetTime(0.6f);
	die->SetTime(0.3f);
	// Cập nhật vào cơ sở dữ liệu
	this->animations[BossWizardState::idle] = idle;
	this->animations[BossWizardState::running] = running;
	this->animations[BossWizardState::flying] = flying;
	this->animations[BossWizardState::fire] = fire;
	this->animations[BossWizardState::flying_fire] = flying_fire;
	this->animations[BossWizardState::punching_fire] = punching_fire;
	this->animations[BossWizardState::punching] = punching;
	this->animations[BossWizardState::beaten] = beaten;
	this->animations[BossWizardState::die] = die;

	//End load resources
	this->current_state = BossWizardState::flying;
	this->current_road = BossWizardRoad::idle;
	this->animation = this->animations[current_state];
	this->previous_state = 0;
	this->time_invisible = 0;
	this->SetVelocityY(BOSS_WIZARD_VELOCITY_Y);
	this->time_die = 0;
	this->previous_hp = this->hp;
	Entity::size.cx = 20;
	Entity::size.cy = 48;
	this->UpdateOneTime = false;
	this->UpdateOneTime2 = false;

}


BossWizard::~BossWizard()
{
	for (int i = 0; i < 7; i++) {
		delete this->animations[i];
	}
}

void BossWizard::Update(float dt)
{
	Enemy::Update(dt);
	BossWizard* boss = BossWizard::GetInstance();
	if (this->time_beaten >= ENEMY_TIME_BEATEN*3 ) {		
		boss->ChangeRoad(new BossWizardBeatenRoad());
	}
	if (this->UpdateOneTime2 == false && this->hp <= 0) {
		boss->ChangeRoad(new BossWizardBeatenRoad());
		this->UpdateOneTime2 = true;
		goto CHECK;
	}
	CHECK:
	if (boss->GetCurrentRoad() == BossWizardRoad::RoadType::beaten) {
		boss->time_beaten -= dt;
	}
	else {
		if (boss->time_beaten < 0) {
			boss->time_beaten = 0;
		}
		if (boss->time_beaten > 0) {
			boss->time_beaten -= dt;			
		}
	}
	if (this->hp <= 10) {
		this->IsLac = true;
		if (this->UpdateOneTime == false) {
			SoundManager::GetInstance()->Stop(SoundManager::SoundList::boss_wizard_theme);
			SoundManager::GetInstance()->PlayRepeat(SoundManager::SoundList::main_theme);
			this->UpdateOneTime = true;
		}
	}
	this->state->Update(dt);
	this->road->Update(dt);
	this->time_invisible -= dt;
	
}

void BossWizard::Draw()
{
	D3DCOLOR color = SceneManager::GetInstance()->GetCurrentScene()->GetMode() & 1 == 1 ? D3DCOLOR_XRGB(255, 255, 255) : D3DCOLOR_XRGB(0, 0, 0);
	BossWizard *boss = BossWizard::GetInstance();
	if (this->IsLac) {
		goto CHECK2;
	}
	if (this->IsBeaten) {
		if (this->IsDie) {
			goto CHECK2;
		}
		this->animation->Draw(this->position, color);
		
		goto CHECK;

	}
	if (this->time_beaten == 0) {
		this->animation->Draw(this->position, color);

	}
	if (this->time_beaten > 0 || this->time_beaten < 0) {
		this->time_beaten -= 0.016;
		CHECK2:
		if (this->time_beaten <= 0) {
			this->time_beaten = 0;
		}
		if ((i++) % 3 == 1) {
			this->animation->Draw(this->position, color);

		}
	}
	CHECK:
	if (boss->GetMoveDirection()) {
		boss->GetCurrentAnimation()->SetScale(1, 1);
	}
	else {
		boss->GetCurrentAnimation()->SetScale(-1, 1);
	}

}

void BossWizard::HandleInput(float dt)
{

}
bool BossWizard::IsCollisionWithGround(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = BOSS_WIZARD_SIZE_WIDTH;
	FootSize.cy = BOSS_WIZARD_FOOT_HEIGHT;
	int direction_y = BossWizard::GetInstance()->GetJumpDirection() == Entity::Entity_Jump_Direction::BotToTop ? 1 : -1;
	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, velocity.x*dt, abs(velocity.y)*dt*direction_y);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();

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
				position.y = item->GetPosition().y + (BOSS_WIZARD_SIZE_HEIGHT + item->GetSize().cy) / 2 - 4;
				velocity.y = 0;
				return true;
			}
		}
	}
	return false;
}

CollisionOut BossWizard::IsCollisionWithWall(float dt, int delta_y)
{
	SIZE FootSize;
	FootSize.cx = BOSS_WIZARD_SIZE_WIDTH;
	FootSize.cy = BOSS_WIZARD_SIZE_HEIGHT;
	int direction_x = BossWizard::GetInstance()->GetMoveDirection() == Entity::Entity_Direction::LeftToRight ? 1 : -1;
	int direction_y = BossWizard::GetInstance()->GetJumpDirection() == Entity::Entity_Jump_Direction::BotToTop ? 1 : -1;

	BoundingBox foot(D3DXVECTOR2(position.x, position.y - delta_y), FootSize, abs(velocity.x*dt)*direction_x, abs(velocity.y)*dt*direction_y);
	auto Checker = Collision::getInstance();
	vector<Entity*> obj = *SceneManager::GetInstance()->GetCurrentScene()->GetCurrentMap()->GetMapObj();

	CollisionOut tmp, ret;
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
				if (BossWizard::GetInstance()->GetJumpDirection() == Entity::Entity_Jump_Direction::BotToTop) {
					continue;
				}
				position.y = item->GetPosition().y + (BOSS_WIZARD_SIZE_HEIGHT + item->GetSize().cy) / 2 - delta_y;
				velocity.y = 0;
				return tmp;
			case CollisionSide::top:
				position.y = item->GetPosition().y - (BOSS_WIZARD_SIZE_HEIGHT + item->GetSize().cy) / 2 + delta_y - 2;
				velocity.y = 0;
				return tmp;
			case CollisionSide::left:
				if (ret.side == CollisionSide::right)
					return tmp;
				position.x = item->GetPosition().x + (BOSS_WIZARD_SIZE_WIDTH + item->GetSize().cx) / 2 + 2;
				velocity.x = 0;
				ret = tmp;
				//return tmp;
			case CollisionSide::right:
				if (ret.side == CollisionSide::left)
					return tmp;
				position.x = item->GetPosition().x - (BOSS_WIZARD_SIZE_WIDTH + item->GetSize().cx) / 2 - 2;
				velocity.x = 0;
				ret = tmp;
				//return tmp;
			default:
				continue;
			}
		}
	}
	return ret;
}

int BossWizard::OnCollision(Entity *obj, float dt)
{
	if (this->IsBeaten == false)
	{
		if (obj->GetType() == Entity::Entity_Type::player_weapon_type
			&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
		{
			if (this->time_beaten <= 0) {

				if (obj->GetTag() == Entity::Entity_Tag::shield) {
					if (Shield::GetInstance()->GetShieldState()->GetCurrentState() == ShieldState::NameState::ShieldDown)
					{
						this->hp -= Shield::GetInstance()->GetShieldState()->GetDamage();
						goto CHECK;
					}
					if (Shield::GetInstance()->GetShieldState()->GetCurrentState() == ShieldState::NameState::Nomal)
					{
						goto CHECK2;
					}
					this->previous_hp = this->hp;
					this->hp -= Shield::GetInstance()->GetShieldState()->GetDamage();
						this->time_beaten = ENEMY_TIME_BEATEN * 3;
				}
				else {
					// PUNCH - KICH
					this->previous_hp = this->hp;
					this->hp -= 2;

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
			&& player->GetCurrentState() != PlayerState::shield_down
			&& player->time_invisible <= 0
			&& Collision::getInstance()->IsCollide(this->GetBoundingBox(), obj->GetBoundingBox()))
		{
			if (this->time_beaten == 0) {
				this->time_beaten = ENEMY_TIME_BEATEN * 3;
				this->previous_hp = this->hp;
				this->hp--;

			}
			player->ChangeState(new PlayerBeatenState(ENEMY_DAMAGE));
		}
		else {
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

void BossWizard::Init()
{
	this->state = new BossWizardFlyingState();
	this->road = new BossWizardIdleRoad();
}

void BossWizard::ChangeState(BossWizardState *new_state)
{
	delete this->state;
	state = new_state;
	this->current_state = state->GetCurrentState();
	this->SetCurrentAnimation(this->animations[current_state]);
}

void BossWizard::ChangeRoad(BossWizardRoad * new_road)
{
	delete this->road;
	this->road = new_road;
	this->current_road = road->GetCurrentRoad();

}

BossWizardState::NameState BossWizard::GetCurrentState()
{
	return this->current_state;
}

BossWizardRoad::RoadType BossWizard::GetCurrentRoad()
{
	return this->current_road;
}

BossWizardState * BossWizard::GetBossWizardState()
{
	return this->state;

}


void BossWizard::SetCurrentState(BossWizardState::NameState new_state)
{
	this->current_state = new_state;
}

void BossWizard::SetCurrentRoad(BossWizardRoad::RoadType new_road)
{
	this->current_road = new_road;
}

void BossWizard::SetCurrentAnimation(Animation * animation)
{
	this->previous_state = this->animation->GetName();
	this->animation = animation;
}

Animation * BossWizard::GetCurrentAnimation()
{
	return this->animation;
}

Animation * BossWizard::GetAnimation(BossWizardState::NameState state)
{
	return this->animations[state];
}

int BossWizard::GetPreviousState()
{
	return this->previous_state;
}