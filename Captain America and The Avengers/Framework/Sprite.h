#pragma once
#include <Windows.h>
#include <d3dx9.h>

class Sprite
{
public:
	Sprite(int ID);
	Sprite(LPCWSTR Path, D3DCOLOR TransparentColor);
	virtual void Draw(D3DCOLOR ColorMode = DefaultColorMode);
	virtual void Draw(D3DXVECTOR2 WorldPosition, D3DCOLOR ColorMode = DefaultColorMode);
	virtual void Draw(FLOAT WorldPositionX, FLOAT WorldPositionY, D3DCOLOR ColorMode = DefaultColorMode);
	virtual void DrawInt(D3DCOLOR ColorMode = DefaultColorMode);
	virtual void DrawInt(D3DXVECTOR2 WorldPosition, D3DCOLOR ColorMode = DefaultColorMode);
	virtual void DrawInt(INT WorldPositionX, INT WorldPositionY, D3DCOLOR ColorMode = DefaultColorMode);
	void ImperiouslyDraw(D3DCOLOR ColorMode = DefaultColorMode); // Only call inside other draw function

	void SetPosition(D3DXVECTOR2 Position); // Set tam render
	void SetPosition(FLOAT x, FLOAT y); // Set tam render
	void SetRotation(float radian);
	void SetRotation(int degree);
	void SetScale(D3DXVECTOR2 Scale); // Set Scale
	void SetScale(FLOAT dx, FLOAT dy); // Set Scale

	D3DXMATRIX GetMatrix();
	D3DXIMAGE_INFO *GetInfo();
protected:

	void SetRect(RECT Rect);
	void SetRect(LONG top, LONG bottom, LONG left, LONG right);

	RECT rect; // rect render
	D3DXVECTOR2 Position; // Tam sprite
	D3DXVECTOR2 CenterRect; // Tam cua rect
	D3DXVECTOR2 Scale;
	D3DXMATRIX Matrix;
	float Rotation;

	LPDIRECT3DTEXTURE9 texture;
	D3DXIMAGE_INFO Info;
	static D3DCOLOR DefaultColorMode;

	~Sprite() {};
private:
	void UpdateMatrix();
	void Init(int ID);
};