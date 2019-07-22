#pragma once
#include "Entity.h"
#include "PlayerState.h"
#include <map>
#include "Collision.h"

// Player
#define PLAYER_SIZE_WIDTH 8
#define PLAYER_SIZE_HEIGHT 40
#define PLAYER_FOOT_HEIGHT 8
//
#define VELOCITY_X 80.0f
#define VELOCITY_Y 150.0f
// jumping
#define DELTA_JUMP VELOCITY_X
#define DISTANCE_JUMPING 90.0f
#define TIME_AIR 0.40f
#define TIME_JUMPING 0.30f
#define TIME_ROLLING 0.4f
#define TIME_KICKING 0.2f
#define JUMPING_ACCELERATION 20.0F
#define ROLLING_ACCELERATION 20.0f
#define JUMPING_VELOCITY_BEGIN 300.0f
#define ROLLING_ACCELERATION 20.0f
// Dashing
#define TIME_DASHING 0.016 * 30
#define TIME_DUCK_BEFORE_DASHING  0.016* 1
#define TIME_WAIT_DASHING 0.016f * 1
// Throwing
#define TIME_THROWING 0.016 * 14
#define TIME_WAIT_THROWING 0.016f * 4
// Punching
#define TIME_PUNCHING 0.016 * 13
#define TIME_WAIT_PUNCHING 0.016f * 4
// Ducking - Punching
#define TIME_DUCKING_PUNCHING 0.016f*10
#define TIME_WAITING_DUCKING_PUNCHING 0.016*4
// Ducking
#define TIME_DUCKING_BEFORE_IDLE 0.016*5
// flowing
#define TIME_JUMPING_DOWN_BEFORE_FLOWING 0.016f*23
#define TIME_ANIMATION_BEFORE_FLOWING 0.5
// diving
// don tho
#define TIME_DON_THO 0.016f*10
using namespace std;
class Player : public Entity
{
public:
	
	static Player* GetInstance();
	void Release();
	void Update(float dt);
	void Render();
	void Draw();
	void HandleInput(float dt);
	void Init();
	void ChangeState(PlayerState* new_state);
	PlayerState::NameState GetCurrentState();
	PlayerState* GetPlayerState();
	void SetCurrentState(PlayerState::NameState new_state);
	void SetCurrentAnimation(Animation* animation);

	Animation* GetCurrentAnimation();
	Animation* GetAnimation(PlayerState::NameState state);
	int GetPreviousState();

	void AddTimeBuffer(float dt);
	float GetTimeBuffer();
	void SetTimeBuffer(float dt);
	void SetIsRolling(bool IsRolling);
	bool GetIsRolling();
	void SetIsThrowing(bool IsThrowing);
	bool GetIsThrowing();
	D3DXVECTOR2 GetPositionIdle();
	Entity::Entity_Direction previous_direction;
	void SetIsDuckingPunching(bool IsDuckingpunching);
	bool GetIsDuckingPunching();
	bool IsCollisionWithGround(float dt, int delta_y = 12);
	bool IsCollisionWithWater(float dt, int delta_y = 12);
	bool IsCollisionWithWall(float dt, int delta_y = 3);

	// Các biến này đáng lẽ phải ở riêng mỗi state, nhưng ở kicking, khi chuyển từ
	// kicking về jumping, jumpingdown hay rolling thì lại phải tạo mới state,
	// như vậy thì time_on_air sẽ được reset lại
	float time_air_rolling;
	float time_air_jumping;
	float time_kicking;
	float time_ducking_before_idle;
	float time_jumping_before_flowing;
	float time_don_tho;
	// Code đi rời để biết tại sao phải tạo những biến này, có một vấn đề là các trạng thái
	// khi new sẽ khởi tạo vận tốc khác nhau, nên khi jumping -> kicking -> jumping thì vận tốc
	// bị khởi động lại 1 lần nữa, những biến này sẽ do idle có quyền định đoạt
	bool IsJumpingDown;
	bool IsJumping;
	bool IsRolling;
	bool IsThrowing;
	bool IsDuckingPunching;
	bool IsFlowing;
	bool IsDonTho;
	bool IsOnAir;
	bool IsLockCollision;
	bool IsShieldDown;
	bool OnTheWater;
	//bool IsShiledDownOnTheWater;
protected:
	static Player *instance;
	std::map<int, Animation*> animations;
	PlayerState::NameState current_state;
	int previous_state;

	PlayerState* player_state;
	Animation* animation;
	D3DXVECTOR2 position_idle;
	float time_buffer;

private:
	Player();
	~Player();
};

