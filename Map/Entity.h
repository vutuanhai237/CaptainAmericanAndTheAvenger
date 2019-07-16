#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "BoxCollider.h"
class Entity
{
public:
	// enum zone
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
		// fyler object
		fly_wall,
		// static object
		ground,
		wall,
		climb_wall,
		// item
		item_container,
		item,
		// camera
		camera_rect,
		// boss
		boss,
		boss_weapon,
		boss_bullet,
		// enemy
		cannon,
		cannon_bullet,
		flyer,
		container,
		soldier,
		soldier_bullet,
		// none
		none
	};
	enum Entity_Type {
		static_type,
		player_type,
		player_weapon_type,
		enemy_type,
		enemy_weapon_type,
		item_type,
		none_type,
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
	enum Status_Item {
		AvailableItem,
		UnavailableItem
	};
	struct CollsionResult {
		bool isCollided;
		BoxCollider region;
	};
	// function zone
	Entity();
	virtual ~Entity();
	virtual void SetActive(bool _IsActive);
	virtual bool GetActive();
	virtual void SetTag(Entity_Tag _tag);
	virtual Entity_Tag GetTag();
	virtual void SetType(Entity_Type _type);
	virtual Entity_Type GetType();
	virtual void SetStatic(bool _IsStatic);
	virtual void SetAliveState(Entity_AliveState _alive);
	virtual void SetVelocity(D3DXVECTOR2 _velocity);
	virtual void SetVelocity(float x, float y);
	virtual void SetPosition(float x, float y);
	virtual D3DXVECTOR2 GetPosition();
	virtual D3DXVECTOR2 GetVelocity();
	virtual float GetVelocityX();
	virtual void SetVelocityX(float x);
	virtual void AddVelocityX(float dx);
	virtual float GetVelocityY();
	virtual void SetVelocityY(float y);
	virtual void AddVelocityY(float dy);
	virtual void SetIsOnAir(float IsOnAir);
	virtual bool GetIsOnAir();

	virtual void SetPositionX(float x);
	virtual void SetPositionY(float y);




	virtual void SetMoveDirection(Entity_Direction _direction);
	virtual Entity_Direction GetMoveDirection();
	virtual void Update(float dt);





protected:
	bool IsStatic;
	bool IsActive;
	int ID;
	Entity_Tag tag;
	Entity_Type type;
	Entity_AliveState alive_state;
	Entity_Direction direction;

	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	//size of entity
	float width;
	float height;
	bool IsOnAir;
};

