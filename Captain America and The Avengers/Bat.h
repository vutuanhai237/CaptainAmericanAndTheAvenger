#pragma once
#include "Enemy.h"
// properties for bat
#define BAT_HP 2
#define BAT_DAMAGE 2
#define BAT_TIME_IDLE 0.9f
#define BAT_SIZE_WIDTH 8
#define BAT_SIZE_HEIGHT 44
#define BAT_FOOT_HEIGHT 8
#define BAT_VELOCITY_Y 100
#define BAT_VELOCITY_X 100
// Distance for each phase
#define BAT_DISTANCE_PHASE_2_12 35
#define BAT_DISTANCE_PHASE_3_11 50
#define BAT_DISTANCE_PHASE_4_10 60
#define BAT_DISTANCE_PHASE_5_7_9 100
#define BAT_DISTANCE_PHASE_6_8 45
class Bat : public Enemy
{
private:
	Animation* idle_ani; // bat normal in egg
	Animation* idle2_ani; // bat electric idle
	Animation* flying_ani; // bat normal flying
	Animation* flying2_ani; // bat electric flying
public:
	enum BatState {
		idle = 21,
		idle2 = 22,
		flying = 23,
		flying2 = 24
	};
	enum Level {
		normal,
		electric
	};
	int i;
	int phase;
	Level level;
	BatState current_state;
	BatState previous_state;
	// scaler
	float distance;
	float time_idle;
	// bool var
	bool active;
	bool IsChamDatLanDau;
	bool UpdateOneTime;
	bool UpdateOneTime2;
	bool IsRunning;
	bool IsVoDich;
	// Function
	virtual void Update(float dt);
	virtual void UpdateElectricLevel(float dt);
	virtual void UpdateNormalLevel(float dt);
	virtual void Draw();
	BoundingBox GetBoundingBox() override;
	// Process collision
	virtual int OnCollision(Entity*, float dt);
	bool IsCollisionWithGround(float dt, int delta_y = 12);
	bool IsCollisionWithSpike(float dt, int delta_y = 12);
	Bat(int level, D3DXVECTOR2 position_spawn);
	~Bat() override;
};

