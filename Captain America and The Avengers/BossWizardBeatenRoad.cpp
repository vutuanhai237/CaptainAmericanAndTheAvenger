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
	// xử lý nội cảnh
	if (this->e != NULL) {
		if (boss->GetMoveDirection() == Entity::Entity_Direction::RightToLeft) {
			//if (boss->GetPosition().x <= 234.5) {
				boss->SetPositionX(boss->GetPosition().x + 0.5);
			//}
			
			if (this->count_jump++ < 5) {
				boss->SetPositionY(boss->GetPosition().y + 1);
			}
			else {
				boss->SetPositionY(boss->GetPosition().y - 1);

			}
			
		}
		else {
			//if (boss->GetPosition().x > 20) {
				boss->SetPositionX(boss->GetPosition().x + 0.5);
			//}
			if (this->count_jump++ < 5) {
				boss->SetPositionY(boss->GetPosition().y + 1);
			}
			else {
				boss->SetPositionY(boss->GetPosition().y - 1);

			}
		}
		
	}
	if (boss->hp <= 0) {
		if (this->UpdateOneTime == false) {
			boss->ChangeState(new BossWizardDieState());
			boss->IsDie = true;
			this->UpdateOneTime = true;
		}
		return;
	}
	else {
		if (boss->GetPosition().x == this->position_goto.x) {
			if (boss->IsCollisionWithWall(dt).CollisionTime < 1.0f) {
				boss->ChangeRoad(new BossWizardIdleRoad());
				boss->ChangeState(new BossWizardIdleState());
			}
			else {
				this->e = NULL;
				boss->SetPositionY(boss->GetPosition().y - 2);

			}
			return;
		}
		if (this->UpdateOneTime == false) {
			boss->ChangeState(new BossWizardBeatenState());
			if (boss->GetMoveDirection() == Entity::Entity_Direction::RightToLeft) {
				position_goto = D3DXVECTOR2(boss->GetPosition().x + 10, boss->GetPosition().y + 10);
				if (position_goto.x >= 234.5) {
					int du = 234.5 - boss->GetPosition().x;
					position_goto.x = 234.5;
					position_goto.y = boss->GetPosition().y + du;
				}
			}
			else {
				position_goto = D3DXVECTOR2(boss->GetPosition().x - 10, boss->GetPosition().y + 10);
				if (position_goto.x <= 20) {
					int du = boss->GetPosition().x - 20;
					position_goto.x = 20;
					position_goto.y = boss->GetPosition().y + du;
				}
			}
			this->e = new Equation(boss->GetPosition(), position_goto);
			this->UpdateOneTime = true;
		}
		return;
	}
}

BossWizardBeatenRoad::BossWizardBeatenRoad()
{
	this->phase = 1;
	this->GetOneTime = false;
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentRoad(BossWizardRoad::RoadType::beaten);
	this->current_road = BossWizardRoad::RoadType::beaten;
	this->position_goto = D3DXVECTOR2(0, 0);
	this->UpdateOneTime = false;
	this->count_jump = 0;
}


BossWizardBeatenRoad::~BossWizardBeatenRoad()
{
}
