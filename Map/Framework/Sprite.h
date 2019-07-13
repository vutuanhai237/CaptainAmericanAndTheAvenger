#pragma once
#include <Windows.h>
#include <d3dx9.h>

class Sprite
{
public:
	Sprite(int ID);
	Sprite(LPCWSTR Path, D3DXCOLOR TransparentColor);
	virtual void Draw();
	
	void SetPosition(D3DXVECTOR2 Position); // Set tam render
	void SetPosition(FLOAT x, FLOAT y); // Set tam render
	void SetRotation(float radian);
	void SetRotation(int degree);
	void SetScale(D3DXVECTOR2 Scale); // Set Scale
	void SetScale(FLOAT dx, FLOAT dy); // Set Scale
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

	~Sprite() {};
private:
	void UpdateMatrix();
};