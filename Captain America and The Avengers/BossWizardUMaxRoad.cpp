#include "BossWizardUMaxRoad.h"
#include "BossWizardFlyingState.h"
#include "BossWizardIdleRoad.h"
#include "BossWizardFlyingFireState.h"
#include "Framework//Debug.h"
void BossWizardUMaxRoad::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	
	if (this->GetOneTime == false) {
		// tạo ngoại cảnh
		boss->ChangeState(new BossWizardFlyingState());
		this->direction_u_max = boss->GetMoveDirection();

		if (0 <= boss->GetPosition().x && boss->GetPosition().x <= 48) {
			boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		}
		if (206 <= boss->GetPosition().x && boss->GetPosition().x <= 256) {
			boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		}
	
		this->GetOneTime = true;
	}
	// xử lý nội cảnh
	if (this->phase == 1) {
		if (this->UpdateOneTime2 == false) {
			boss->ChangeState(new BossWizardIdleState());
			boss->SetVelocity(0, 0);
			this->UpdateOneTime2 == true;
		}
		this->time_idle_before_jump += dt;
		if (this->time_idle_before_jump > 0.5f) {
			this->time_idle_before_jump = 0;
			boss->ChangeState(new BossWizardFlyingState());
			this->phase++;
		}
		return;
	}
	if (this->phase == 2) {
		boss->SetVelocity(0, BOSS_WIZARD_VELOCITY_Y);
		this->FireOneTime = false;
		boss->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
	}
	if (this->phase == 3) {
		if (this->UpdateOneTime == false) {
			boss->SetVelocity(BOSS_WIZARD_FLYING_VELOCITY_X, 0);
		/*	if (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
				boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			}
			else {
				boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
			}*/
			this->UpdateOneTime = true;
		}
	
		if (this->FireOneTime == false) {
			boss->ChangeState(new BossWizardFlyingFireState(true));
			this->FireOneTime = true;
		}

	}
	if (this->phase == 4) {
		boss->ChangeState(new BossWizardFlyingState());
		boss->SetVelocity(0, BOSS_WIZARD_VELOCITY_Y);
		boss->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
	}
	if (this->phase == 5) {
		if (this->loop > 0) {
			this->loop--;
			this->Release();
			return;
		}
		boss->IsUMax = false;
		boss->IsIdle = true;
		boss->ChangeRoad(new BossWizardIdleRoad());
		return;
	}

	if (boss->IsCollisionWithWall(dt).CollisionTime < 1.0f) {
		this->phase++;

	}

}

void BossWizardUMaxRoad::Release()
{
	this->direction_u_max = Entity::Entity_Direction::LeftToRight;
	this->phase = 1;
	this->GetOneTime = false;
	this->FireOneTime = false;
	this->time_fire = 0.0f;
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentRoad(BossWizardRoad::RoadType::u_max);
	this->current_road = BossWizardRoad::RoadType::u_max;
	boss->IsUMax = true;
	this->UpdateOneTime = false;
	this->UpdateOneTime2 = false;

	this->time_idle_before_jump = 0.0f;

}

BossWizardUMaxRoad::BossWizardUMaxRoad()
{
	this->direction_u_max = Entity::Entity_Direction::LeftToRight;
	this->phase = 1;
	this->GetOneTime = false;
	this->FireOneTime = false;
	this->time_fire = 0.0f;
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentRoad(BossWizardRoad::RoadType::u_max);
	this->current_road = BossWizardRoad::RoadType::u_max;
	boss->IsUMax = true;
	if (boss->hp <= 10) {
		this->loop = rand() % 3 + 1;

	}
	this->loop = rand() % 1 + 1;
	this->UpdateOneTime = false;
	this->UpdateOneTime2 = false;

	this->time_idle_before_jump = 0.0f;

}


BossWizardUMaxRoad::~BossWizardUMaxRoad()
{
}
