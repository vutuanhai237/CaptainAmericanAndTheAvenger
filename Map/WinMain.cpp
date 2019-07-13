#include "GameManager.h"
#include "Framework/d3d.h"
#include "Framework/DirectInput.h"
#include "Framework/GameTimer.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (d3d::GetInstance()->Init(hInstance, nCmdShow))
		return FALSE;
	if (DirectInput::GetInstance()->Init(d3d::GetInstance()->GetHWND()))
		return FALSE;
	GameManager::GetInstance()->Init(60);
	

	MSG msg;
	bool done = false;

	while (!done)
	{
		GameTimer::GetInstance()->StartCounter();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				done = true;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			GameManager::GetInstance()->Running();
	}

	GameManager::GetInstance()->Release();
	return msg.wParam;
}