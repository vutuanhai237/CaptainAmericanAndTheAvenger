#include "BossWizardIdleState.h"
#include "BossWizardFlyingState.h"
#include "BossWizardRunningState.h"
#include "BossWizardPunchingFireState.h"
#include "EnergyBullet.h"
#include "LaserBullet.h"
BossWizardPunchingFireState::BossWizardPunchingFireState()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::punching_fire);
	this->current_state = BossWizardState::NameState::punching_fire;
	boss->SetVelocity(0, 0);
	boss->SetSize(20, 45);
	this->time_punching_fire = 0; // để bắn ngay lúc bắt đầu state
	this->count_bullet = 0;
}


BossWizardPunchingFireState::~BossWizardPunchingFireState()
{
}

void BossWizardPunchingFireState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);
	this->time_punching_fire += dt;
	if (this->time_punching_fire >= BOSS_WIZARD_TIME_FIRING*1.2) {
		if (this->count_bullet < BOSS_WIZARD_MAX_BULLET_PUNCHING_FIRE) {
			time_punching_fire = 0.0f;
			if (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
				SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
					new EnergyBullet(
						D3DXVECTOR2(boss->GetPosition().x + 20, boss->GetPosition().y + 5),
						boss->GetMoveDirection()
					)
				);
			}
			else {
				SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
					new EnergyBullet(
						D3DXVECTOR2(boss->GetPosition().x - 20, boss->GetPosition().y + 5),
						boss->GetMoveDirection()
					)
				);
			}
		}
		
		this->count_bullet++;
	}
	if (this->time_punching_fire >= BOSS_WIZARD_TIME_PUNCHING_FIRE) {
		boss->ChangeState(new BossWizardIdleState());
		return;
	}
	else {
		return;
	}

}

void BossWizardPunchingFireState::Draw()
{
}

BoundingBox BossWizardPunchingFireState::GetBoundingBox()
{
	return BoundingBox();
}

void BossWizardPunchingFireState::HandleInput(float dt)
{
}
