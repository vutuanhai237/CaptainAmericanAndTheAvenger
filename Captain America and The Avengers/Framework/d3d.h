#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

class d3d
{
public:
	static d3d* GetInstance();
	HWND GetHWND();
	LPDIRECT3D9 GetD3d();
	LPDIRECT3DDEVICE9 GetDevice();
	LPD3DXSPRITE GetSpriteHander();
	LPDIRECT3DSURFACE9 GetBackbuffer();

	DWORD Init(HINSTANCE hInstance, int nCmdShow);
	void Release();
private:
	d3d() {};
	~d3d();
	
	HWND hWnd = NULL;
	LPDIRECT3D9 d3d9 = NULL;
	LPDIRECT3DDEVICE9 d3ddev = NULL;
	LPD3DXSPRITE SpriteHander = NULL;
	LPDIRECT3DSURFACE9 BackBuffer = NULL;
	static d3d *Instance;
};