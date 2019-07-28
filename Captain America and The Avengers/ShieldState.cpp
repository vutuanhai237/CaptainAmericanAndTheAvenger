#include "ShieldState.h"

ShieldState::ShieldState()
{
	CurrentState = NameState::Nomal;
	VirtualPoint = D3DXVECTOR2(0, 0);
}

ShieldState::ShieldState(NameState State)
{
	CurrentState = State;
}

void ShieldState::SetCurrentState(NameState State)
{
	CurrentState = State;
}

ShieldState::NameState ShieldState::GetCurrentState()
{
	return CurrentState;
}

BoundingBox ShieldState::GetBoundingBox()
{
	SIZE size;
	size.cx = 7;
	size.cy = 25;
	return BoundingBox(VirtualPoint, size, 0, 0);
}

int ShieldState::GetFrameLock()
{
	return this->FrameLock;
}

D3DXVECTOR2 ShieldState::GetVirtualPoint()
{
	return VirtualPoint;
}
