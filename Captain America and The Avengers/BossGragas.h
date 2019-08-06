#pragma once
#include "Enemy.h"
#include "Collision.h"
#include "BossWizardState.h"
#include "BossWizardIdleState.h"
#include "BossWizardRoad.h"
// Boss Gragas properties
#define BOSS_GRAGAS_DAMAGE 2
#define BOSS_GRAGAS_HP 20
#define BOSS_GRAGAS_SIZE_WIDTH 8
#define BOSS_GRAGAS_SIZE_HEIGHT 48
#define BOSS_GRAGAS_FOOT_HEIGHT 8
#define BOSS_GRAGAS_ARM_HEIGHT 8
#define BOSS_GRAGAS_VELOCITY_X 80
#define BOSS_GRAGAS_VELOCITY_Y 200
// idle state properties
#define BOSS_GRAGAS_TIME_IDLE 1.0f
#define BOSS_GRAGAS_TIME_IDLE_BEFORE_DIE 2.5f
// throwing state properties
#define BOSS_GRAGAS_TIME_THROWING 1.50f
// firing state properties
#define BOSS_GRAGAS_TIME_FIRING 2.0f
// running state properties
#define BOSS_GRAGAS_DISTANCE_RUNNING 180
// beaten state properties
#define BOSS_GRAGAS_TIME_BEATEN 1.5f

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
	// get
	BossGragas::NameState GetCurrentState();
	Animation* GetCurrentAnimation();
	Animation* GetAnimation(BossGragas::NameState state);
	int GetPreviousState();
	// set
	void SetCurrentState(BossGragas::NameState new_state);
	void SetCurrentAnimation(Animation* animation);
	// collsion
	CollisionOut IsCollisionWithWall(float dt, int delta_y = 4);
	int OnCollision(Entity*, float dt) override;
	// properties
	int count_bullet;
	int previous_hp;
	int phase;
	int j;
	int previous_state;
	int count_barrel_explode;
	float time_idle;
	float time_runnig;
	float time_fire;
	float time_throwing;
	float time_invisible;
	float time_beaten;
	float time_gong;
	float time_die;
	float distance_running;
	bool IsChamDatLanDau;
	bool UpdateOneTime;
	bool IsUpdateRunDirection;
	bool UpdateOneTime2;
	// enum
	Mode mode;
	Entity::Entity_Direction run_direction;
	Entity::Entity_Direction previous_direction;
protected:
	static BossGragas *instance;
	std::map<int, Animation*> animations;
	BossGragas::NameState current_state;
	Animation* animation;
private:
	BossGragas();
	~BossGragas();
};

