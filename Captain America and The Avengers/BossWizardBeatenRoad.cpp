#include "BossWizardBeatenRoad.h"
#include "BossWizardBeatenState.h"
#include "BossWizardDieState.h"
#include "BossWizardIdleState.h"
#include "BossWizardIdleRoad.h"
#include "BossWizard.h"
void BossWizardBeatenRoad::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	if (this->GetOneTime == false) {
		// tạo ngoại cảnh
		boss->SetVelocity(0, 0);
		this->GetOneTime = true;
	}
	
	CollisionOut out = boss->IsCollisionWithWall(dt);
	if (out.CollisionTime < 1.0f && out.side != CollisionSide::top && this->delta_lui >= 10)
	{	

	if (boss->IsOnAir == true) {
			if (out.side == CollisionSide::bottom) {
				if (boss->hp <= 0) {
					if (this->UpdateOneTime == false) {
						boss->ChangeState(new BossWizardDieState());
						boss->IsDie = true;
						this->UpdateOneTime = true;
					}
					return;
				}
				boss->previous_state = 7;
				boss->SetVelocity(0, 0);
				boss->ChangeRoad(new BossWizardIdleRoad());
				boss->ChangeState(new BossWizardIdleState());
				return;
			}
			else {
				boss->SetVelocityY(BOSS_WIZARD_FLYING_VELOCITY_X);
				boss->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
				goto CHECK;
			}
		
		}
		else {
			if (boss->hp <= 0) {
				if (this->UpdateOneTime == false) {
					boss->previous_state = 7;
					boss->ChangeState(new BossWizardDieState());
					boss->IsDie = true;
					this->UpdateOneTime = true;
				}
				return;
			}
			boss->previous_state = 7;
			boss->SetVelocity(0, 0);
			boss->ChangeRoad(new BossWizardIdleRoad());
			boss->ChangeState(new BossWizardIdleState());
			return;
		}
		
	}
CHECK:
	if (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
		boss->SetPositionX(boss->GetPosition().x - 1);
		if (delta_lui <= 5) {
			boss->SetVelocity(0, BOSS_WIZARD_FLYING_VELOCITY_X/10);
			if (boss->GetPosition().y > 70) {
				boss->SetVelocity(0, BOSS_WIZARD_FLYING_VELOCITY_X);

			}
			boss->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
		}
		if (delta_lui >5 && delta_lui <= 10) {
			boss->SetVelocity(0, BOSS_WIZARD_FLYING_VELOCITY_X/10);
			if (boss->GetPosition().y > 70) {
				boss->SetVelocity(0, BOSS_WIZARD_FLYING_VELOCITY_X);

			}
			boss->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
		}
		this->delta_lui += 1;
		return;
	}
	if (boss->GetMoveDirection() == Entity::Entity_Direction::RightToLeft) {
		boss->SetPositionX(boss->GetPosition().x + 1);
		if (delta_lui <= 5) {
			boss->SetVelocity(0, BOSS_WIZARD_FLYING_VELOCITY_X/10);
			if (boss->GetPosition().y > 70) {
				boss->SetVelocity(0, BOSS_WIZARD_FLYING_VELOCITY_X);

			}
			boss->SetJumpDirection(Entity::Entity_Jump_Direction::BotToTop);
		}
		if (delta_lui > 5 && delta_lui <= 10) {
			boss->SetVelocity(0, BOSS_WIZARD_FLYING_VELOCITY_X/10);
			if (boss->GetPosition().y > 70) {
				boss->SetVelocity(0, BOSS_WIZARD_FLYING_VELOCITY_X);

			}
			boss->SetJumpDirection(Entity::Entity_Jump_Direction::TopToBot);
		}
		this->delta_lui += 1;
		return;
	}
}

BossWizardBeatenRoad::BossWizardBeatenRoad()
{
	this->GetOneTime = false;
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentRoad(BossWizardRoad::RoadType::beaten);
	boss->ChangeState(new BossWizardBeatenState());
	this->current_road = BossWizardRoad::RoadType::beaten;
	//boss->IsOnAir = false;
	this->position_goto = D3DXVECTOR2(0, 0);
	this->UpdateOneTime = false;
	this->count_jump = 0;
	this->previous_y = boss->GetPosition().y;
	this->delta_lui = 0;
	this->previous_y = boss->GetPosition().y;
}


BossWizardBeatenRoad::~BossWizardBeatenRoad()
{
}
