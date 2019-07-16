#include "DirectInput.h"
#include "Debug.h"

DirectInput* DirectInput::Instance = NULL;
DirectInput* DirectInput::GetInstance()
{
	if (!Instance) Instance = new DirectInput();
	return Instance;
}
HRESULT DirectInput::Init(HWND hWnd)
{
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, NULL);
	if (result != DI_OK)
	{
		Debug::PrintOut(L"[Error code %d] Error while create Input device!", &result);
		return result;
	}
	result = dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
	if (result != DI_OK)
	{
		Debug::PrintOut(L"[Error code %d] Error while create Input Keyboard!", &result);
		return result;
	}
	result = dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	result = dikeyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);;
	result = dikeyboard->Acquire();

	result = dinput->CreateDevice(GUID_SysMouse, &dimouse, NULL);
	if (result != DI_OK)
	{
		Debug::PrintOut(L"[Error code %d] Error while create Input Mouse!", &result);
		return result;
	}
	result = dimouse->SetDataFormat(&c_dfDIMouse);
	result = dimouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	result = dimouse->Acquire();
	if (result != DI_OK)	
		Debug::PrintOut(L"[Error code %d] Error while Acquire Mouse!", &result);	
	return result;
}
void DirectInput::KeySnapShot()
{
	HRESULT result = dikeyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
	while (result != DI_OK && (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) )
	{
		//Debug::PrintOut(L"[Error code %d] Error while Acquire Keyboard!", &result);
		result = dikeyboard->Acquire();
	}
	dikeyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
}

void DirectInput::MouseSnapShot()
{
	dimouse->GetDeviceState(sizeof(mouse_state), (LPVOID)&mouse_state);
}

int DirectInput::KeyDown(int key)
{
	return ((keys[key] & 0x80)) ? true : false;
}

int DirectInput::KeyReleased(int key)
{
	this->SetTimePressed(key, 0);
	return ((keys[key] & 0x80)) ? false : true;

}

int DirectInput::KeyPressed(int key, float dt)
{
	this->UpdateTimePressed(key, dt);
	return (time_pressed[key] > TIME_PRESSED) ? true : false;

}

void DirectInput::ProcessKeyboard()
{
	HRESULT hr;

	// Collect all key states first
	hr = dikeyboard->GetDeviceState(sizeof(keys), keys);
	if (FAILED(hr))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
		{
			HRESULT h = dikeyboard->Acquire();
			if (h == DI_OK)
			{
				Debug::PrintOut(L"[INFO] Keyboard re-acquired!\n");
			}
			else return;
		}
		else
		{
			Debug::PrintOut(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
			return;
		}
	}

	keyHandler->KeyState((BYTE *)&keys);



	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	hr = dikeyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
	if (FAILED(hr))
	{
		Debug::PrintOut(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
		return;
	}

	// Scan through all buffered events, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = keyEvents[i].dwOfs;
		int KeyState = keyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			keyHandler->OnKeyDown(KeyCode);
		else
			keyHandler->OnKeyUp(KeyCode);
	}
}

void DirectInput::Release()
{
	delete Instance;
}

float DirectInput::GetTimePressed(int key)
{
	return this->time_pressed[key];
}

void DirectInput::SetTimePressed(int key, float dt)
{
	this->time_pressed[key] = dt;
}

void DirectInput::UpdateTimePressed(int key, float dt)
{
	this->time_pressed[key] += dt;
}



DirectInput::~DirectInput()
{
	if (dikeyboard != NULL)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL;
	}
	if (dimouse != NULL)
	{
		dimouse->Unacquire();
		dimouse->Release();
		dimouse = NULL;
	}
	if (dinput != NULL)
		dinput->Release();
}
