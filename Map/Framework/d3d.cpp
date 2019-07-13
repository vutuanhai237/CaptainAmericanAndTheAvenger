#include "d3d.h"
#include "GameSetting.h"
#include "Debug.h"

d3d* d3d::Instance = NULL;

d3d* d3d::GetInstance()
{
	if (!Instance)
		Instance = new d3d();
	return Instance;
}

HWND d3d::GetHWND()
{
	return hWnd;
}

LPDIRECT3D9 d3d::GetD3d()
{
	return d3d9;
}

LPDIRECT3DDEVICE9 d3d::GetDevice()
{
	return d3ddev;
}

LPD3DXSPRITE d3d::GetSpriteHander()
{
	return SpriteHander;
}

LPDIRECT3DSURFACE9 d3d::GetBackbuffer()
{
	return BackBuffer;
}

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

DWORD d3d::Init(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GAME_CLASS;
	wc.hIconSm = NULL;
	RegisterClassEx(&wc);

	DWORD ErrorCode;
	hWnd = CreateWindow(GAME_CLASS, GAME_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT, NULL, NULL, hInstance, NULL);
	if (!hWnd)
	{
		ErrorCode = GetLastError();
		Debug::PrintOut(L"[Error code %d] Create window failed!\n", &ErrorCode);
		return ErrorCode;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d9)
	{
		ErrorCode = GetLastError();
		Debug::PrintOut(L"[Error code %d] Error initializing Direct3D!\n", &ErrorCode);
		return ErrorCode;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp)); // Clear data before use
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = GAME_SCREEN_WIDTH;
	d3dpp.BackBufferHeight = GAME_SCREEN_HEIGHT;
	d3dpp.BackBufferCount = 1;
	d3dpp.hDeviceWindow = hWnd;
	d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev); // Create device into d3ddev
	if (d3ddev == NULL)
	{
		ErrorCode = GetLastError();
		Debug::PrintOut(L"[Error code %d] Failed to create device!\n", &ErrorCode);
		return ErrorCode;
	}

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &BackBuffer); // Create Pointer to the BackBuffer

	return D3DXCreateSprite(d3ddev, &SpriteHander);
}

void d3d::Release()
{
	delete Instance;
}

d3d::~d3d()
{
	if (d3d9)
		d3d9->Release();
	if (d3ddev)
		d3ddev->Release();
	if (BackBuffer)
		BackBuffer->Release();
}
