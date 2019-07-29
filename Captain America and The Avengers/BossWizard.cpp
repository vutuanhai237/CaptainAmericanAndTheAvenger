#include "BossWizard.h"
#include "BossWizardFlyingState.h"
BossWizard*BossWizard::instance = NULL;

BossWizard * BossWizard::GetInstance()
{
	if (!instance)
		instance = new BossWizard();
	return instance;
}

void BossWizard::Release()
{
	delete instance;
}

BossWizard::BossWizard() :Enemy()
{
	///
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
	Animation* flying_fire = new Animation(BossWizardState::NameState::flying_fire, L"Resources//Enemy//BossWizard/BossWizardFlyingFire.png", D3DCOLOR_XRGB(0, 166, 81), 2);
	Animation* punching = new Animation(BossWizardState::NameState::punching, L"Resources//Enemy//BossWizard/BossWizardPunching.png", D3DCOLOR_XRGB(0, 166, 81), 2);
	Animation* punching_fire = new Animation(BossWizardState::NameState::punching_fire, L"Resources//Enemy//BossWizard/BossWizardPunchingFire.png", D3DCOLOR_XRGB(0, 166, 81), 2);
	Animation* beaten = new Animation(BossWizardState::NameState::beaten, L"Resources//Enemy//BossWizard/BossWizardBeaten.png", D3DCOLOR_XRGB(0, 166, 81), 3);
	// Chỉ những animation nào có số sprite > 1 thì mới set time
	running->SetTime(0.1f);
	idle->SetTime(0.2f); idle->SetFrameReset(2);
	fire->SetTime(0.1f);
	flying->SetTime(1000000.0f);
	flying_fire->SetTime(0.1f);
	punching->SetTime(0.1f);
	punching_fire->SetTime(0.1f);
	beaten->SetTime(0.1f);
	// Cập nhật vào cơ sở dữ liệu
	this->animations[BossWizardState::idle] = idle;
	this->animations[BossWizardState::running] = running;
	this->animations[BossWizardState::flying] = flying;
	this->animations[BossWizardState::fire] = fire;
	this->animations[BossWizardState::flying_fire] = flying_fire;
	this->animations[BossWizardState::punching_fire] = punching_fire;
	this->animations[BossWizardState::punching] = punching;
	this->animations[BossWizardState::beaten] = beaten;
	//End load resources
	this->current_state = BossWizardState::flying;
	this->animation = this->animations[current_state];
	this->previous_state = 0;
	this->time_invisible = 0;
	this->SetVelocityY(BOSS_WIZARD_VELOCITY_Y);
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
	this->BossWizard_state->Update(dt);
	this->time_invisible -= dt;
}

void BossWizard::Draw()
{
	BossWizard *boss = BossWizard::GetInstance();
	if (this->time_invisible <= 0) {
		this->animation->Draw(this->position);
	}
	else {

		if (this->time_invisible <= 0) {
			this->time_invisible = 0;
		}
		if ((i++) % 3 == 1) {
			this->animation->Draw(this->position);

		}

	}
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
				position.y = item->GetPosition().y + BOSS_WIZARD_SIZE_HEIGHT / 2;
				return true;
			}
		}
	}
	return false;
}

bool BossWizard::IsCollisionWithWall(float dt, int delta_y)
{
	
	bool ret = false;

	Entity::IsLocking = false;
	Entity::Update(dt);
	Entity::IsLocking = true;

	SIZE PlayerSize;
	PlayerSize.cx = BOSS_WIZARD_SIZE_WIDTH;
	PlayerSize.cy = BOSS_WIZARD_SIZE_HEIGHT;
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
				position.x = item->GetPosition().x + (item->GetSize().cx + BOSS_WIZARD_SIZE_WIDTH) / 2 + 1;
				if (this->GetCurrentState() != PlayerState::NameState::jumping)
					return true;
				ret = true;
				break;
			case CollisionSide::right:
				position.x = item->GetPosition().x - (item->GetSize().cx + BOSS_WIZARD_SIZE_WIDTH) / 2 - 1;
				if (this->GetCurrentState() != PlayerState::NameState::jumping)
					return true;
				ret = true;
				break;
			case CollisionSide::top:
				position.y = item->GetPosition().y - (item->GetSize().cy + BOSS_WIZARD_SIZE_HEIGHT) / 2;
				velocity.y = 0.0f;
				return true;
			case CollisionSide::bottom:
				if (this->GetCurrentState() == PlayerState::NameState::jumping)
					return false;
				position.y = item->GetPosition().y + (item->GetSize().cy + BOSS_WIZARD_SIZE_HEIGHT) / 2 - delta_y;
				velocity.y = 0.0f;
				return true;
			default:
				break;
			}
		}
	}
	return ret;


}

void BossWizard::Init()
{
	this->BossWizard_state = new BossWizardFlyingState();
}

void BossWizard::ChangeState(BossWizardState *new_state)
{
	delete this->BossWizard_state;
	BossWizard_state = new_state;
	this->current_state = BossWizard_state->GetCurrentState();
	this->SetCurrentAnimation(this->animations[current_state]);
}

BossWizardState::NameState BossWizard::GetCurrentState()
{
	return this->current_state;
}

BossWizardState * BossWizard::GetBossWizardState()
{
	return this->BossWizard_state;

}


void BossWizard::SetCurrentState(BossWizardState::NameState new_state)
{
	this->current_state = new_state;
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

int BossWizard::OnCollision(Entity *obj, float dt)
{
	return Enemy::OnCollision(obj, dt);

}

BoundingBox BossWizard::GetBoundingBox()
{
	return this->BossWizard_state->GetBoundingBox();
}