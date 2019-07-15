#pragma once
#include <InitGuid.h>
#include <dinput.h>
#define KEYBOARD_BUFFER_SIZE 1024
class KeyEventHandler
{
public:
	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};

typedef KeyEventHandler * LPKeyEventHandler;
class DirectInput
{
public:
	static DirectInput* GetInstance();
	HRESULT Init(HWND hWnd);
	void KeySnapShot();
	void MouseSnapShot();
	int KeyDown(int DIK_key);
	int GetKeyDown(int DIK_key);
	void ProcessKeyboard();
	void Release();
private:
	DirectInput() {};
	~DirectInput();

	LPDIRECTINPUT8 dinput = NULL;
	LPDIRECTINPUTDEVICE8 dikeyboard = NULL;
	LPDIRECTINPUTDEVICE8 dimouse = NULL;
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	LPKeyEventHandler keyHandler;

	char keys[256];
	DIMOUSESTATE mouse_state;
	static DirectInput* Instance;
};