#pragma once
#include "Enemy.h"
#include "BossWizardState.h"
#include "Collision.h"
#include "BossWizardIdleState.h"
#include "BossWizardRoad.h"
// BossWizard
#define BOSS_GRAGAS_DAMAGE 2
#define BOSS_GRAGAS_HP 30
#define BOSS_GRAGAS_LOW_HP 10
#define BOSS_GRAGAS_SIZE_WIDTH 8
#define BOSS_GRAGAS_SIZE_HEIGHT 48
#define BOSS_GRAGAS_FOOT_HEIGHT 8
#define BOSS_GRAGAS_ARM_HEIGHT 8
#define BOSS_GRAGAS_VELOCITY_X 80
#define BOSS_GRAGAS_VELOCITY_Y 200
// idle
#define BOSS_GRAGAS_TIME_IDLE 1.0f
// throwing
#define BOSS_GRAGAS_TIME_THROWING 1.50f
// firing
#define BOSS_GRAGAS_TIME_FIRING 2.0f
// running
#define BOSS_GRAGAS_DISTANCE_RUNNING 160
// beaten
#define BOSS_GRAGAS_TIME_BEATEN 1.0f
using namespace std;
class BossGragas : public Enemy
{
public:
	enum NameState {
		falling,
		idle,
		running,
		firing,
		beaten,
		throwing,
		running2,
		idle2
	};
	enum Mode {
		normal,
		crazy
	};
	static BossGragas* GetInstance();
	void Release();
	void Update(float dt);
	void Draw();
	void Init();
	void UpdateNormalPhase(float dt);
	void UpdateCrazyPhase(float dt);

	BossGragas::NameState GetCurrentState();
	Animation* GetCurrentAnimation();
	Animation* GetAnimation(BossGragas::NameState state);
	void SetCurrentState(BossGragas::NameState new_state);
	void SetCurrentAnimation(Animation* animation);
	int GetPreviousState();
	CollisionOut IsCollisionWithWall(float dt, int delta_y = 4);
	int OnCollision(Entity*, float dt) override;
	// properties
	int count_bullet;
	int previous_hp;
	float time_idle;
	float time_runnig;
	float time_fire;
	float time_throwing;
	float time_invisible;
	float time_beaten;
	float time_die;
	Mode mode;
	int phase;
	bool IsChamDatLanDau;
	bool UpdateOneTime;
	float distance_running;
	int count_barrel_explode = 0;
	Entity::Entity_Direction run_direction;
	Entity::Entity_Direction previous_direction;

protected:
	static BossGragas *instance;
	std::map<int, Animation*> animations;
	BossGragas::NameState current_state;
	int previous_state;
	Animation* animation;
	int i = 0;
private:
	BossGragas();
	~BossGragas();
};

