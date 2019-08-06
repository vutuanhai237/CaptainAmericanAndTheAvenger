#include "EnergyBullet.h"
#include "BossWizardFlyingFireState.h"

BossWizardFlyingFireState::BossWizardFlyingFireState(bool IsFire)
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::flying_fire);
	this->current_state = BossWizardState::NameState::flying_fire;
	boss->SetSize(20, 45);
	this->count_bullet = 0;
	this->IsFire = IsFire;
}

BossWizardFlyingFireState::~BossWizardFlyingFireState()
{
}

void BossWizardFlyingFireState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);
	if (abs(Player::GetInstance()->GetPosition().x-BossWizard::GetInstance()->GetPosition().x) < 15
		&& this->count_bullet < BOSS_WIZARD_MAX_BULLET_FLYING && this->IsFire) 
	{
		if (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) {
			SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
				new EnergyBullet(
					D3DXVECTOR2(boss->GetPosition().x + 15, boss->GetPosition().y - 9),
					boss->GetMoveDirection(),
					-ENERGY_BULLET_VELOCITY_X
				)
			);
		}
		else 
		{
			SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
				new EnergyBullet(
					D3DXVECTOR2(boss->GetPosition().x - 15, boss->GetPosition().y - 9),
					boss->GetMoveDirection(),
					-ENERGY_BULLET_VELOCITY_X
				)
			);
		}
		this->count_bullet++;
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