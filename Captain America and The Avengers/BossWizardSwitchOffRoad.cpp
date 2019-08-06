#include "BossWizardSwitchOffRoad.h"
#include "BossWizardUMaxRoad.h"
#include "BossWizardPunchingState.h"
#include "BossWizardFlyingState.h"
#include "BossWizardIdleRoad.h"
#include "BossWizard.h"
#include "SceneManager.h"

void BossWizardSwitchOffRoad::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	if (this->GetOneTime == false)
	{
		// tạo ngoại cảnh
		boss->ChangeState(new BossWizardFlyingState());
		if (boss->GetPosition().x <= 70)
		{
			boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		}
		else 
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
			boss->ChangeState(new BossWizardIdleState());
			boss->IsOnAir = false;
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

	if (this->phase == 2) {
		boss->SetVelocity(0, BOSS_WIZARD_VELOCITY_Y);
		boss->IsOnAir = true;
		this->FireOneTime = false;
		boss->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop); 
	}

	if (this->phase == 3) 
	{
		if (this->UpdateOneTime == false) 
		{
			boss->IsOnAir = true;
			boss->SetVelocity(BOSS_WIZARD_FLYING_VELOCITY_X, 0);
			this->UpdateOneTime = true;
		}
		if (boss->GetPosition().x <= 75 && boss->GetPosition().x >= 70) 
		{
			this->phase++;
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
		if (this->UpdateOneTime3 == false) {
			boss->ChangeState(new BossWizardPunchingState());
			boss->IsOnAir = false;
			if (boss->GetPosition().x <= 90) 
			{
				boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
			}
			else 
			{
				boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			}
			boss->SetVelocity(0, 0);
			this->UpdateOneTime3 = true;
		}
		this->time_idle_before_jump += dt;
		if (this->time_idle_before_jump > 0.15f) 
		{
			if (SceneManager::GetInstance()->GetCurrentScene()->GetMode() & 1)
			{
				SceneManager::GetInstance()->GetCurrentScene()->SwapMap();
			}
		}
		if (this->time_idle_before_jump > 0.5f) 
		{			
			this->time_idle_before_jump = 0;
			this->phase++;
		}
		return;
	}

	if (this->phase == 6) 
	{
		if (this->e != NULL && IsJumping) 
		{
			this->IsJumpingFirst++;
			boss->SetPositionY(e->GetYFromX(boss->GetPosition().x));
		}

		if (this->IsJumpingFirst >= 10 && boss->IsCollisionWithWall(dt).CollisionTime < 1.0f)
		{
			this->IsJumping = false;
			boss->ChangeRoad(new BossWizardIdleRoad());
			boss->ChangeState(new BossWizardIdleState());
			boss->IsOnAir = false;
			return;
		}
		if (this->UpdateOneTime4 == false)
		{
			boss->ChangeState(new BossWizardFlyingState());
			boss->IsOnAir = true;
			boss->SetVelocity(BOSS_WIZARD_VELOCITY_X, 0);
			this->e = new Equation(
				boss->GetPosition(),
				D3DXVECTOR2(boss->GetPosition().x + (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight ? 1 : -1) * 35, boss->GetPosition().y + 10)
			);
			this->IsJumping = true;
			this->UpdateOneTime4 = true;
		}
	}
	if (boss->IsCollisionWithWall(dt).CollisionTime < 1.0f)
	{
		this->phase++; 
		return;
	}

	if (this->UpdateOneTime4 == false && boss->IsCollisionWithGround(dt))
	{
		this->phase++; 
		return;
	}
}

BossWizardSwitchOffRoad::BossWizardSwitchOffRoad()
{	
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentRoad(BossWizardRoad::RoadType::switch_off);
	this->current_road = BossWizardRoad::RoadType::switch_off;
	boss->IsUMax = true;
	this->UpdateOneTime = false;
	this->UpdateOneTime2 = false;
	this->UpdateOneTime3 = false;
	this->UpdateOneTime4 = false;
	this->GetOneTime = false;
	this->FireOneTime = false;
	this->IsJumping = false;
	this->phase = 1;
	this->time_idle_before_jump = 0.0f;
	this->IsJumpingFirst = 0;
	this->e = NULL;
}

BossWizardSwitchOffRoad::~BossWizardSwitchOffRoad()
{
}
