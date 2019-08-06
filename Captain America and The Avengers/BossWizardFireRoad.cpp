#include "BossWizardFireRoad.h"
#include "BossWizardUMaxRoad.h"
#include "BossWizardRunningState.h"
#include "BossWizardPunchingState.h"
#include "BossWizardFireState.h"
#include "BossWizardFlyingState.h"
#include "BossWizardPunchingFireState.h"
#include "BossWizardIdleRoad.h"
#include "BossWizard.h"

void BossWizardFireRoad::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	if (this->GetOneTime == false)
	{
		boss->SetVelocity(BOSS_WIZARD_VELOCITY_X, 0);
		if (boss->GetPosition().x > Player::GetInstance()->GetPosition().x) 
		{
			boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		}
		else 
		{
			boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		}
		this->GetOneTime = true;
	}
	// xử lý nội cảnh
	if (abs(boss->GetPosition().y - Player::GetInstance()->GetPosition().y) > 10.0f)
	{
		this->time_laugh += dt;
		if (this->time_laugh > 3.0f) 
		{
			boss->ChangeRoad(new BossWizardIdleRoad());
			return;
		}
	}
	else
	{
		this->time_laugh = 0;
	}

	if (this->IsRunning)
	{	
		this->time_running += dt;
		if (this->UpdateOneTime == false)
		{
			boss->ChangeState(new BossWizardRunningState());
			boss->IsOnAir = false;
			boss->SetVelocity(BOSS_WIZARD_VELOCITY_X, 0);
			this->UpdateOneTime = true;
			if (boss->GetPosition().x > Player::GetInstance()->GetPosition().x) 
			{
				boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			}
			else 
			{
				boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
			}
		}
		if (this->time_running >= 0.5f) 
		{
			this->IsRunning = false;
			this->time_running = 0;
			this->UpdateOneTime = false;
			if (abs(boss->GetPosition().x - Player::GetInstance()->GetPosition().x) <= 85
				&& abs(boss->GetPosition().x - Player::GetInstance()->GetPosition().x) >= 32)
			{
				this->phase = 3;
			}
		}
		return;
	}

	if (this->phase == 1 && IsRunning == false)
	{
		this->time_fire += dt;
		if (this->UpdateOneTime == false)
		{
			boss->ChangeState(new BossWizardFireState(2));
			boss->SetVelocity(0, 0);
			boss->IsOnAir = false;
			this->UpdateOneTime = true;
		}
		if (this->time_fire >= BOSS_WIZARD_TIME_FIRE)
		{
			this->IsRunning = true;
			this->time_fire = 0;
			this->phase++;
			this->UpdateOneTime = false;
		}	
	}
	if (this->phase == 2 && IsRunning == false) 
	{
		this->time_fire += dt;
		if (this->UpdateOneTime == false) {
			boss->ChangeState(new BossWizardFireState(3));
			boss->IsOnAir = false;
			boss->SetVelocity(0, 0);
			this->UpdateOneTime = true;
		}
		if (this->time_fire >= BOSS_WIZARD_TIME_FIRE)
		{
			this->IsRunning = true;
			this->time_fire = 0;
			this->UpdateOneTime = false;
		}
	}
	if (this->phase == 3 && IsRunning == false)
	{
		this->time_fire += dt;
		if (this->UpdateOneTime == false) 
		{
			boss->ChangeState(new BossWizardPunchingFireState());
			boss->SetVelocity(0, 0);
			this->UpdateOneTime = true;
		}
		if (this->time_fire >= BOSS_WIZARD_TIME_FIRE)
		{
			this->IsRunning = false;
			this->time_fire = 0;
			this->UpdateOneTime = false;
			this->phase++;
		}
	}
	if (this->phase == 4 && IsRunning == false)
	{	
		if (this->e != NULL && IsJumping) 
		{ 
			this->IsJumpingFirst++;
			boss->SetPositionY(e->GetYFromX(boss->GetPosition().x)); 
		}
		CollisionOut out = boss->IsCollisionWithWall(dt);
		if (this->IsJumpingFirst >= 10 && out.CollisionTime < 1)
		{
			this->IsJumping = false;
			if (boss->hp < boss->previous_hp)
			{
				boss->ChangeRoad(new BossWizardUMaxRoad());
				boss->ChangeState(new BossWizardFlyingState());
				return;
			}
			if (out.side == CollisionSide::bottom)
			{
				boss->IsIdle = true;
				boss->previous_state = 2;
				boss->IsOnAir = false;
				boss->ChangeRoad(new BossWizardIdleRoad());
				boss->ChangeState(new BossWizardIdleState());
				return;
			}			
			return;
		}

		if (this->UpdateOneTime == false)
		{
			boss->ChangeState(new BossWizardFlyingState());
			boss->IsOnAir = true;
			boss->SetVelocity(BOSS_WIZARD_VELOCITY_X, 0);
			int distance_jump = (int)boss->GetPosition().x;
			if (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight)
			{
				distance_jump += 70; 
				if (distance_jump > 220) 
				{ 
					distance_jump = 220; 
					boss->SetVelocity(BOSS_WIZARD_VELOCITY_X * 0.5, 0); 
				}
			}
			if (boss->GetMoveDirection() == Entity::Entity_Direction::RightToLeft) 
			{
				distance_jump -= 70; 
				if (distance_jump < 30) { 
					distance_jump = 30; 
					boss->SetVelocity(BOSS_WIZARD_VELOCITY_X * 0.5, 0); 
				}
			}
			this->e = new Equation(boss->GetPosition(), D3DXVECTOR2((FLOAT)distance_jump, (FLOAT)(boss->GetPosition().y + 48)));
			this->IsJumping = true;
			this->UpdateOneTime = true;
		}
		if (this->time_fire >= BOSS_WIZARD_TIME_FIRE)
		{
			this->IsRunning = true;
			this->time_fire = 0;
			this->UpdateOneTime = false;
		}
	}
}

BossWizardFireRoad::BossWizardFireRoad()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentRoad(BossWizardRoad::RoadType::idle);
	this->current_road = BossWizardRoad::RoadType::idle;
	this->GetOneTime = false;
	this->IsRunning = false;
	this->IsFiring = false;
	this->UpdateOneTime = false;
	this->IsJumping = false;
	boss->IsOnAir = false;
	this->phase = 1;
	this->IsJumpingFirst = 0;
	this->time_laugh = 0.0f;
	this->time_fire = 0.0f;
	this->time_running = 0.0f;
}

BossWizardFireRoad::~BossWizardFireRoad()
{
}