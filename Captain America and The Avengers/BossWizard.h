#pragma once
#include "Enemy.h"
#include "BossWizardState.h"
#include "Collision.h"
#include "BossWizardIdleState.h"
#include "BossWizardRoad.h"
// BossWizard
#define BOSS_WIZARD_SIZE_WIDTH 8
#define BOSS_WIZARD_SIZE_HEIGHT 52
#define BOSS_WIZARD_FOOT_HEIGHT 8
#define BOSS_WIZARD_ARM_HEIGHT 8
//
#define BOSS_WIZARD_VELOCITY_X 80.0f
#define BOSS_WIZARD_FLYING_VELOCITY_X 160.0f
#define BOSS_WIZARD_VELOCITY_Y 150.0f

// Fire zone
#define BOSS_WIZARD_TIME_FIRE 1.0f
#define BOSS_WIZARD_TIME_FIRING 0.2f
#define BOSS_WIZARD_TIME_WAITING_BEFORE_FIRE_FOUR_BULLET 0.3f
#define BOSS_WIZARD_MAX_BULLET 3
#define BOSS_WIZARD_MAX_LASER_BULLET 3
// Punch zone
#define BOSS_WIZARD_TIME_PUNCHING 0.2f
// Flying Fire zone
#define BOSS_WIZARD_TIME_FLYING_FIRE 0.2f
#define BOSS_WIZARD_TIME_FLYING_FIRING 0.1f
#define BOSS_WIZARD_MAX_BULLET_FLYING 1
// Punching fire
#define BOSS_WIZARD_TIME_PUNCHING_FIRE 0.2f 
#define BOSS_WIZARD_MAX_BULLET_PUNCHING_FIRE 1
using namespace std;
class BossWizard : public Enemy
{
public:
	enum AttackOption {
		energy_only, // bắn năng lượng đơn
		energy_laser3, // bắn 3 laser và 1 năng lượng sau cùng
		energy_laser2, // 
		punch,
	};
	static BossWizard* GetInstance();
	void Release();
	void Update(float dt);
	void Draw();
	void HandleInput(float dt);
	void Init();
	void ChangeState(BossWizardState* new_state);
	void ChangeRoad(BossWizardRoad* new_road);
	BossWizardState::NameState GetCurrentState();
	
	BossWizardState* GetBossWizardState();
	Animation* GetCurrentAnimation();
	Animation* GetAnimation(BossWizardState::NameState state);
	void SetCurrentState(BossWizardState::NameState new_state);
	BossWizardRoad::RoadType GetCurrentRoad();
	void SetCurrentRoad(BossWizardRoad::RoadType new_road);
	void SetCurrentAnimation(Animation* animation);
	int GetPreviousState();
	virtual int OnCollision(Entity *, float dt);
	bool IsCollisionWithGround(float dt, int delta_y = 12);
	bool IsCollisionWithWall(float dt, int delta_y = 4);

	BoundingBox GetBoundingBox();

	float time_flying;
	float time_runnig;
	float time_fire;
	float time_punching;
	float time_invisible;
	// ROAD ZONE
	bool IsIdle = false;
	bool IsUMax = false;
	bool IsUMin = false;



protected:
	static BossWizard *instance;
	std::map<int, Animation*> animations;

	BossWizardState::NameState current_state;
	int previous_state;

	BossWizardRoad::RoadType current_road;
	int previous_road;

	BossWizardState* state;
	BossWizardRoad* road;

	Animation* animation;
	D3DXVECTOR2 position_idle;
	float time_buffer;
	int i = 0;
private:
	BossWizard();
	~BossWizard();
};

