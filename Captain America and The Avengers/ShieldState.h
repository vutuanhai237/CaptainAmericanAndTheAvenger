#pragma once
#include <d3dx9.h>
#include "Collision.h"

class ShieldState
{
public:
	enum NameState
	{
		Nomal,
		OnAir,
		ShieldUp, 
		ShieldAttack,
		ShieldDown,
		ShieldKick
	};
	ShieldState();
	ShieldState(NameState State);
	virtual int GetDamage() { return 0; };
	virtual void Update(float dt) {};
	virtual void Draw() {};
	virtual BoundingBox GetBoundingBox(); // Nomal
	int GetFrameLock();

	D3DXVECTOR2 GetVirtualPoint();

	void SetCurrentState(NameState State);
	NameState GetCurrentState();
protected:
	NameState CurrentState;
	int FrameLock;
	D3DXVECTOR2 VirtualPoint;
};