#include "BossWizardIdleState.h"
#include "BossWizardFlyingState.h"
#include "BossWizardRunningState.h"
#include "BossWizardDieState.h"
#include "EnergyBullet.h"
#include "LaserBullet.h"
#include "SceneManager.h"
BossWizardDieState::BossWizardDieState()
{
	BossWizard* boss = BossWizard::GetInstance();
	boss->SetCurrentState(BossWizardState::NameState::die);
	this->current_state = BossWizardState::NameState::die;
	boss->SetVelocity(0, 0);
	boss->SetSize(20, 45);
	this->time_die = 0;
}


BossWizardDieState::~BossWizardDieState()
{
}

void BossWizardDieState::Update(float dt)
{
	BossWizard* boss = BossWizard::GetInstance();
	Player* player = Player::GetInstance();
	boss->GetCurrentAnimation()->Update(dt);
	this->time_die += dt;
	if (this->time_die >= 1.6) {
		SceneManager::GetInstance()->GetCurrentScene()->IsExitAble = true;
	}
}

void BossWizardDieState::Draw()
{
}

BoundingBox BossWizardDieState::GetBoundingBox()
{
	return BoundingBox();
}

void BossWizardDieState::HandleInput(float dt)
{
}
