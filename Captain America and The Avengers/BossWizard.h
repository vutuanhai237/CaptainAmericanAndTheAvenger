#pragma once
#include "Enemy.h"
#include "Collision.h"
#include "BossWizardState.h"
#include "BossWizardIdleState.h"
#include "BossWizardRoad.h"
// Boss Wizard properties zone
#define BOSS_WIZARD_HP 80
#define BOSS_WIZARD_LOW_HP 10
#define BOSS_WIZARD_SIZE_WIDTH 8
#define BOSS_WIZARD_SIZE_HEIGHT 52
#define BOSS_WIZARD_FOOT_HEIGHT 8
#define BOSS_WIZARD_ARM_HEIGHT 8
#define BOSS_WIZARD_VELOCITY_X 80.0f
#define BOSS_WIZARD_FLYING_VELOCITY_X 160.0f
#define BOSS_WIZARD_VELOCITY_Y 150.0f
// Fire zone
#define BOSS_WIZARD_TIME_FIRE 1.0f
#define BOSS_WIZARD_TIME_FIRING 0.38f
#define BOSS_WIZARD_TIME_WAITING_BEFORE_FIRE_FOUR_BULLET 0.3f
#define BOSS_WIZARD_MAX_BULLET 3
#define BOSS_WIZARD_MAX_LASER_BULLET 3
// Punch zone
#define BOSS_WIZARD_TIME_PUNCHING 0.2f
// Flying Fire zone
#define BOSS_WIZARD_TIME_FLYING_FIRE 0.2f
#define BOSS_WIZARD_TIME_FLYING_FIRING 0.1f
#define BOSS_WIZARD_MAX_BULLET_FLYING 1
// Punching fire zone
#define BOSS_WIZARD_TIME_PUNCHING_FIRE 1.2f 
#define BOSS_WIZARD_MAX_BULLET_PUNCHING_FIRE 1
// Beaten zone
#define BOSS_WIZARD_TIME_BEATEN 0.116* 20

using namespace std;

class BossWizard : public Enemy
{
public:
	static BossWizard* GetInstance();
	void Release();
	void Update(float dt);
	void Draw();
	void Init();
	// get
	BossWizardState::NameState GetCurrentState();
	BossWizardState* GetBossWizardState();
	BossWizardRoad::RoadType GetCurrentRoad();
	Animation* GetCurrentAnimation();
	Animation* GetAnimation(BossWizardState::NameState state);
	int GetPreviousState();
	// set 
	void SetCurrentState(BossWizardState::NameState new_state);
	void SetCurrentRoad(BossWizardRoad::RoadType new_road);
	void SetCurrentAnimation(Animation* animation);
	void ChangeState(BossWizardState* new_state);
	void ChangeRoad(BossWizardRoad* new_road);
	// collusion
	int OnCollision(Entity*, float dt) override;
	bool IsCollisionWithGround(float dt, int delta_y = 12);
	CollisionOut IsCollisionWithWall(float dt, int delta_y = 4);
	// time zone
	float time_flying;
	float time_runnig;
	float time_fire;
	float time_punching;
	float time_invisible;
	float time_die;
	int previous_hp;
	int previous_state;
	// flag zone
	bool IsIdle = false;
	bool IsUMax = false;
	bool IsUMin = false;
	bool IsDie = false;
	bool IsLac = false;
	bool IsOnAir = false;
	bool UpdateOneTime;
	bool UpdateOneTime2;
protected:
	static BossWizard *instance;
	std::map<int, Animation*> animations;
	BossWizardState* state;
	BossWizardRoad* road;
	BossWizardState::NameState current_state;
	BossWizardRoad::RoadType current_road;
	Animation* animation;
	float time_buffer;
	int previous_road;
	int i = 0;	
private:
	BossWizard();
	~BossWizard();
};

