#include "EnergyBullet.h"
#include "BossWizardFlyingFireState.h"
#include "BossWizardFlyingState.h"
#include "BossWizardFireState.h"
BossWizardFlyingFireState::BossWizardFlyingFireState()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::flying_fire);
	this->current_state = BossWizardState::NameState::flying_fire;
	boss->SetVelocity(0, 0);
	boss->SetSize(20, 45);
	this->time_flying_fire = 0.0f;
	this->count_bullet = 0;
}


BossWizardFlyingFireState::~BossWizardFlyingFireState()
{
}

void BossWizardFlyingFireState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);
	this->time_flying_fire += dt;
	if (this->time_flying_fire >= BOSS_WIZARD_TIME_FLYING_FIRING 
		&& this->count_bullet < BOSS_WIZARD_MAX_BULLET_FLYING) 
	{
		if (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
			SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
				new EnergyBullet(
					D3DXVECTOR2(boss->GetPosition().x + 15, boss->GetPosition().y - 9),
					boss->GetMoveDirection()
				)
			);
		}
		else {
			SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
				new EnergyBullet(
					D3DXVECTOR2(boss->GetPosition().x - 15, boss->GetPosition().y - 9),
					boss->GetMoveDirection()
				)
			);
		}
		this->count_bullet++;

	}
	if (this->time_flying_fire >= BOSS_WIZARD_TIME_FLYING_FIRE) {
		boss->ChangeState(new BossWizardFlyingState());
		return;
	}
	else {
		return;
	}

}

void BossWizardFlyingFireState::Draw()
{
}

BoundingBox BossWizardFlyingFireState::GetBoundingBox()
{
	return BoundingBox();
}

void BossWizardFlyingFireState::HandleInput(float dt)
{
}
