#include "BossWizardIdleState.h"
#include "BossWizardFlyingState.h"
#include "BossWizardRunningState.h"
#include "BossWizardFireState.h"
#include "EnergyBullet.h"
#include "LaserBullet.h"

BossWizardFireState::BossWizardFireState(int max_laser_bullet)
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::fire);
	this->current_state = BossWizardState::NameState::fire;
	boss->SetVelocity(0, 0);
	boss->SetSize(20, 45);
	this->time_fire = 0.0f;
	this->time_wait_before_fire_energy_bullet = 0.0f;
	this->time_firing = 0.24f;
	this->count_bullet = 0;
	this->max_laser_bullet = max_laser_bullet;
}

BossWizardFireState::~BossWizardFireState()
{
}

void BossWizardFireState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	Player* player = Player::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);
	this->time_fire += dt;
	this->time_firing += dt;
	if (this->time_firing >= BOSS_WIZARD_TIME_FIRING)
	{
		this->time_firing = 0.0f;
		if (this->count_bullet < BOSS_WIZARD_MAX_BULLET)
		{
			if (this->count_bullet < this->max_laser_bullet)
			{
				if (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight)
				{
					SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
						new LaserBullet(
							D3DXVECTOR2(boss->GetPosition().x + 15, boss->GetPosition().y + 9),
							boss->GetMoveDirection(),
							abs(player->GetPosition().y - boss->GetPosition().y)
						)
					);
				}
				else
				{
					SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
						new LaserBullet(
							D3DXVECTOR2(boss->GetPosition().x - 15, boss->GetPosition().y + 9),
							boss->GetMoveDirection(),
							abs(player->GetPosition().y - boss->GetPosition().y)
						)
					);
				}
				this->count_bullet++;
			}
			else {
				if (boss->GetMoveDirection() == Entity::Entity_Direction::LeftToRight) 
				{
					SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
						new EnergyBullet(
							D3DXVECTOR2(boss->GetPosition().x + 15, boss->GetPosition().y + 9),
							boss->GetMoveDirection()
						)
					);
				}
				else
				{
					SceneManager::GetInstance()->GetCurrentScene()->GetCurrentGrid()->AddObject2Cell(
						new EnergyBullet(
							D3DXVECTOR2(boss->GetPosition().x - 15, boss->GetPosition().y + 9),
							boss->GetMoveDirection()
						)
					);
				}
				this->count_bullet++;
			}
		}
	}
	if (this->time_fire >= BOSS_WIZARD_TIME_FIRE)
	{
		return;
	}
}

void BossWizardFireState::Draw()
{
}

BoundingBox BossWizardFireState::GetBoundingBox()
{
	return BoundingBox();
}

void BossWizardFireState::HandleInput(float dt)
{
}