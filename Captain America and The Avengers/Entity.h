#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Collision.h"
#include <math.h>
#include <vector>

// Onllision return:
//	0 : doing nothing
// 1 : delete this (delete object call function OnCollision)
// -1 : delete obj2 (delete object parameter)

class Entity
{
public:
	enum Side_Collision {
		left,
		right,
		top,
		bottom,
		top_left,
		top_right,
		bottom_left,
		bottom_right,
		unknown
	};

	enum Entity_Tag {
		// player
		player,
		shield,
		// flying object
		fly_wall,
		// static object
		water,
		ground,
		wall,
		rope,
		spike,
		// item
		item_container,
		item,
		// door
		door,
		// boss
		boss,
		boss_weapon,
		boss_bullet,
		// enemy
		cannon,
		cannon_bullet,
		flyer,
		redrobotrocket,
		red_rocket,
		blue_soldier,
		soldier_bullet,
		// none
		none,
		item_exit_orb,
		on_off_switch,
		green_soldier,
		// Platform
		disappear_platform,
		moving_platform,
		cross_platform,
		circle_platform,
		gray_robot,
		bat,
		gray_rocket_robot,
		electric_shockwave_barrier
	};

	enum Entity_Type {
		static_type,
		player_type,
		player_weapon_type,
		enemy_type,
		enemy_weapon_type,
		item_type,
		none_type,
		platform
	};

	enum Entity_AliveState {
		Alive,
		Beaten,
		Die,
		Remove
	};

	enum Entity_Direction {
		LeftToRight,
		RightToLeft
	};

	enum Entity_Jump_Direction {
		BotToTop,
		TopToBot
	};

	enum Status_Item {
		AvailableItem,
		UnavailableItem
	};

	Entity();
	virtual ~Entity();
	virtual int OnCollision(Entity *, float dt) { return 0; };
	// active
	virtual void SetActive(bool _IsActive);
	virtual bool GetActive();
	// tag
	virtual void SetTag(Entity_Tag _tag);
	virtual Entity_Tag GetTag();
	// type
	virtual void SetType(Entity_Type _type);
	virtual Entity_Type GetType();
	// static
	virtual void SetStatic(bool _IsStatic);
	// state
	virtual void SetAliveState(Entity_AliveState _alive);
	// velocity
	virtual void SetVelocity(D3DXVECTOR2 _velocity);
	virtual void SetVelocity(float x, float y);
	virtual float GetVelocityX();
	virtual void SetVelocityX(float x);
	virtual void AddVelocityX(float dx);
	virtual float GetVelocityY();
	virtual void SetVelocityY(float y);
	virtual void AddVelocityY(float dy);
	// position
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(D3DXVECTOR2 position);
	virtual D3DXVECTOR2 GetPosition();
	virtual D3DXVECTOR2 GetVelocity();
	virtual void SetPositionX(float x);
	virtual void SetPositionY(float y);
	// direction
	virtual void SetMoveDirection(Entity_Direction _direction);
	virtual Entity_Direction GetMoveDirection();
	virtual void SetJumpDirection(Entity_Jump_Direction _jump_direction);
	virtual Entity_Jump_Direction GetJumpDirection();
	// size
	virtual void SetSize(const SIZE &size);
	virtual void SetSize(long width, long height);
	virtual SIZE GetSize();
	// locking (no update position)
	virtual void SetIsLocking(bool Islocking);
	virtual bool GetIsLocking();
	// other
	virtual void Update(float dt);
	virtual BoundingBox GetBoundingBox();
	virtual void Draw() {};
protected:
	int ID;
	bool IsLocking;
	bool IsStatic;
	bool IsActive;
	BoundingBox box;
	Entity_Tag tag;
	Entity_Type type;
	Entity_AliveState alive_state;
	Entity_Direction direction;
	Entity_Jump_Direction jump_direction;
	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	SIZE size;
};

