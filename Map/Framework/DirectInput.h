#pragma once
#include <InitGuid.h>
#include <dinput.h>
#define KEYBOARD_BUFFER_SIZE 1024
#define TIME_PRESSED 0.06
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
	int KeyDown(int key);
	int KeyReleased(int key);
	int KeyPressed(int key, float dt);
	void ProcessKeyboard();
	void Release();
	float GetTimePressed(int key);
	void SetTimePressed(int key, float dt);
	void UpdateTimePressed(int key, float dt);
private:
	DirectInput() {};
	~DirectInput();

	LPDIRECTINPUT8 dinput = NULL;
	LPDIRECTINPUTDEVICE8 dikeyboard = NULL;
	LPDIRECTINPUTDEVICE8 dimouse = NULL;
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
	LPKeyEventHandler keyHandler;

	char keys[256];
	float time_pressed[256];
	DIMOUSESTATE mouse_state;
	static DirectInput* Instance;
};