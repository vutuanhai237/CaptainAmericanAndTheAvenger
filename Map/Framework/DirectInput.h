#pragma once
#include <InitGuid.h>
#include <dinput.h>

class DirectInput
{
public:
	static DirectInput* GetInstance();
	HRESULT Init(HWND hWnd);
	void KeySnapShot();
	void MouseSnapShot();
	int KeyDown(int DIK_key);
	void Release();
private:
	DirectInput() {};
	~DirectInput();

	LPDIRECTINPUT8 dinput = NULL;
	LPDIRECTINPUTDEVICE8 dikeyboard = NULL;
	LPDIRECTINPUTDEVICE8 dimouse = NULL;

	char keys[256];
	DIMOUSESTATE mouse_state;
	static DirectInput* Instance;
};