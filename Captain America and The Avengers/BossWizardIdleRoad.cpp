#include "BossWizardIdleRoad.h"
#include "BossWizardUMaxRoad.h"
#include "BossWizardSwitchOffRoad.h"
#include "BossWizardRunningState.h"
#include "BossWizardPunchingState.h"
#include "BossWizardFlyingState.h"
#include "BossWizardFireRoad.h"
#include "BossWizard.h"
#include "Framework//DirectInput.h"
void BossWizardIdleRoad::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	auto keyboard = DirectInput::GetInstance();
	
	if (this->GetOneTime == false) {
		// tạo ngoại cảnh
		if ((boss->previous_state == 7 || boss->previous_state == 2) 
			&& boss->IsOnAir == false) {
			boss->SetVelocity(0, 0);
		}
		else {
			if (boss->IsOnAir) {
				boss->SetVelocity(0, BOSS_WIZARD_FLYING_VELOCITY_X);
				boss->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
				if (boss->IsCollisionWithWall(dt).CollisionTime < 1.0f) {
					boss->SetVelocity(0, 0);
					boss->IsOnAir = false;
				}
			}
		}
		boss->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
		
		if (boss->GetPosition().x > Player::GetInstance()->GetPosition().x) {
			boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		}
		else {
			boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		}
		this->GetOneTime = true;
	}
	// xử lý nội cảnh
	if (boss->hp <= BOSS_WIZARD_HP/2 && boss->hp > 10) {
		if (SceneManager::GetInstance()->GetCurrentScene()->GetMode() & 1) {
			boss->ChangeRoad(new BossWizardSwitchOffRoad());
			return;
		}
	}
	if (boss->hp <= 10 && boss->IsIdle == false) {
		boss->ChangeRoad(new BossWizardUMaxRoad());
		boss->ChangeState(new BossWizardFlyingState());
		return;
	}
	// nếu cả 2 ko ở cùng độ cao thì thằng này chỉ biết đứng cười
	if (abs(boss->GetPosition().y - Player::GetInstance()->GetPosition().y) > 10.0f
		&& IsChamDatLanDau) {
		if (boss->GetPosition().x > Player::GetInstance()->GetPosition().x) {
			boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
		}
		else {
			boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
		}
		return;
	}
	// Ở gần thì đấm
	if (abs(boss->GetPosition().x - Player::GetInstance()->GetPosition().x) < 20.0f
		&& IsChamDatLanDau) {
		boss->ChangeState(new BossWizardPunchingState());
		return;
	}
	// Chạy ngắn
	if (this->IsRunning && IsChamDatLanDau) {
		this->time_running += dt;
		boss->SetPositionX(boss->GetPosition().x + 3);
		if (this->time_running >= 1.0f) {
			this->IsRunning = false;
		
		}
	}
	this->time_idle += dt;
	if (this->time_idle >= 1.0f) {
		if (this->IsRunning == false && this->time_running <= 1.0f) {
			if (boss->GetPosition().x > Player::GetInstance()->GetPosition().x) {
				boss->SetMoveDirection(Entity::Entity_Direction::RightToLeft);
			}
			else {
				boss->SetMoveDirection(Entity::Entity_Direction::LeftToRight);
			}
			boss->ChangeRoad(new BossWizardFireRoad());
			return;
		}
	
		return;
	}

	CollisionOut out = boss->IsCollisionWithWall(dt);
	if (out.CollisionTime < 1.0f && out.side == CollisionSide::bottom) {
		this->IsChamDatLanDau = true;
		boss->ChangeState(new BossWizardIdleState());
		boss->SetVelocity(0, 0);
		return;
	}
}

BossWizardIdleRoad::BossWizardIdleRoad()
{
	this->GetOneTime = false;
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentRoad(BossWizardRoad::RoadType::idle);
	this->current_road = BossWizardRoad::RoadType::idle;
	this->time_idle = 0.0f;
	this->phase = 1;
	this->IsChamDatLanDau = false;
	this->time_running = 0.0f;
	this->IsRunning = false;

}


BossWizardIdleRoad::~BossWizardIdleRoad()
{
}
