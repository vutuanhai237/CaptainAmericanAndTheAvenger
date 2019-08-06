#include "BossWizardUMaxRoad.h"
#include "BossWizardFlyingState.h"
#include "BossWizardIdleRoad.h"
#include "BossWizardFlyingFireState.h"
#include "Framework/SoundManager.h"
void BossWizardUMaxRoad::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	if (this->GetOneTime == false) 
	{
		// tạo ngoại cảnh
		boss->ChangeState(new BossWizardFlyingState());
		this->direction_u_max = boss->GetMoveDirection();
		boss->IsOnAir = true;
		if (0 <= boss->GetPosition().x && boss->GetPosition().x <= 48)
		{
			boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		}
		if (206 <= boss->GetPosition().x && boss->GetPosition().x <= 256)
		{
			boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		}
		this->GetOneTime = true;
	}
	// xử lý nội cảnh
	if (this->phase == 1)
	{
		if (this->UpdateOneTime2 == false)
		{
			boss->previous_state = 2;
			boss->IsOnAir = false;
			boss->ChangeState(new BossWizardIdleState());
			boss->SetVelocity(0, 0);
			this->UpdateOneTime2 = true;
		}
		this->time_idle_before_jump += dt;
		if (this->time_idle_before_jump > 0.5f)
		{
			this->time_idle_before_jump = 0;
			boss->ChangeState(new BossWizardFlyingState());
			this->phase++;
		}
		return;
	}

	if (this->phase == 2) 
	{
		boss->SetVelocity(0, BOSS_WIZARD_VELOCITY_Y);
		boss->IsOnAir = true;
		this->FireOneTime = false;
		boss->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
	}

	if (this->phase == 3) 
	{
		if (this->UpdateOneTime == false)
		{
			boss->SetVelocity(BOSS_WIZARD_FLYING_VELOCITY_X, 0);
			boss->IsOnAir = true;
			this->UpdateOneTime = true;
		}
	
		if (this->FireOneTime == false) 
		{
			boss->ChangeState(new BossWizardFlyingFireState(true));
			this->FireOneTime = true;
		}
	}
	if (this->phase == 4)
	{
		boss->ChangeState(new BossWizardFlyingState());
		boss->IsOnAir = true;
		boss->SetVelocity(0, BOSS_WIZARD_VELOCITY_Y);
		boss->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
	}
	if (this->phase == 5)
	{
		if (this->loop > 0) 
		{
			this->loop--;
			this->Release();
			return;
		}
		boss->previous_hp = boss->hp;
		boss->previous_state = 2;
		boss->ChangeState(new BossWizardIdleState());
		boss->ChangeRoad(new BossWizardIdleRoad());
		boss->IsUMax = false;
		boss->IsIdle = true;	
		boss->IsOnAir = false;
		return;
	}

	if (boss->IsCollisionWithWall(dt).CollisionTime < 1.0f) 
	{
		this->phase++;
	}
}

void BossWizardUMaxRoad::Release()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentRoad(BossWizardRoad::RoadType::u_max);
	this->current_road = BossWizardRoad::RoadType::u_max;
	this->direction_u_max = Entity::Entity_Direction::LeftToRight;
	boss->IsUMax = true;
	this->UpdateOneTime = false;
	this->UpdateOneTime2 = false;
	this->GetOneTime = false;
	this->FireOneTime = false;
	this->time_idle_before_jump = 0.0f;
	this->phase = 1;
	this->time_fire = 0.0f;
}

BossWizardUMaxRoad::BossWizardUMaxRoad()
{
	
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentRoad(BossWizardRoad::RoadType::u_max);
	this->current_road = BossWizardRoad::RoadType::u_max;
	this->direction_u_max = Entity::Entity_Direction::LeftToRight;
	if (boss->hp <= 10) {
		this->loop = rand() % 3 + 1;
	}
	boss->IsUMax = true;
	this->UpdateOneTime = false;
	this->UpdateOneTime2 = false;
	this->GetOneTime = false;
	this->FireOneTime = false;
	this->phase = 1;
	this->time_fire = 0.0f;
	this->time_idle_before_jump = 0.0f;
	this->loop = rand() % 1 + 1;
}


BossWizardUMaxRoad::~BossWizardUMaxRoad()
{
}
