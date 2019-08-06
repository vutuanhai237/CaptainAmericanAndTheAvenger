#include "Sprite.h"
#include "Texture.h"
#include "d3d.h"
#include "../Camera.h"

D3DCOLOR Sprite::DefaultColorMode = D3DCOLOR_XRGB(255, 255, 255);

Sprite::Sprite(int ID)
{
	Init(ID);
}

Sprite::Sprite(LPCWSTR Path, D3DCOLOR TransparentColor)
{
	int ID;
	Texture::GetInstance()->Add(ID, Path, TransparentColor);
	Init(ID);
}

void Sprite::Draw(D3DCOLOR ColorMode)
{
	LPD3DXSPRITE Hander = d3d::GetInstance()->GetSpriteHander();
	D3DXMATRIX OldMatrix;
	Hander->GetTransform(&OldMatrix);
	Hander->SetTransform(&Matrix);

	Hander->Begin(D3DXSPRITE_ALPHABLEND);
	Hander->Draw(texture, &rect, NULL, NULL, ColorMode);
	Hander->End();

	Hander->SetTransform(&OldMatrix);
}

void Sprite::Draw(D3DXVECTOR2 WorldPosition, D3DCOLOR ColorMode)
{
	SetPosition(Camera::GetInstance()->World2Render(WorldPosition));
	Draw(ColorMode);
}

void Sprite::Draw(FLOAT X, FLOAT Y, D3DCOLOR ColorMode)
{
	Draw(D3DXVECTOR2(X, Y), ColorMode);
}

void Sprite::DrawInt(D3DCOLOR ColorMode)
{
	Position.x = ceilf(Position.x);
	Position.y = ceilf(Position.y);
	UpdateMatrix();
	Draw(ColorMode);
}

void Sprite::DrawInt(D3DXVECTOR2 WorldPosition, D3DCOLOR ColorMode)
{
	Position = Camera::GetInstance()->World2Render(WorldPosition);
	DrawInt(ColorMode);
}

void Sprite::DrawInt(INT X, INT Y, D3DCOLOR ColorMode)
{
	DrawInt(D3DXVECTOR2((FLOAT)X, (FLOAT)Y), ColorMode);
}

void Sprite::ImperiouslyDraw(D3DCOLOR ColorMode) // Only call inside other draw function
{
	LPD3DXSPRITE Hander = d3d::GetInstance()->GetSpriteHander();
	Hander->SetTransform(&Matrix);
	Hander->Draw(texture, &rect, NULL, NULL, ColorMode);
}

void Sprite::SetRect(RECT Rect)
{
	rect.top = Rect.top;
	rect.bottom = Rect.bottom;
	rect.left = Rect.left;
	rect.right = Rect.right;

	CenterRect.x = (FLOAT)((Rect.right - Rect.left) / 2);
	CenterRect.y = (FLOAT)((Rect.bottom - Rect.top) / 2);

	UpdateMatrix();
}

void Sprite::SetRect(LONG top, LONG bottom, LONG left, LONG right)
{
	rect.top = top;
	rect.bottom = bottom;
	rect.left = left;
	rect.right = right;

	CenterRect.x = (FLOAT)((right - left) / 2);
	CenterRect.y = (FLOAT)((bottom - top) / 2);

	UpdateMatrix();
}

void Sprite::SetPosition(D3DXVECTOR2 Pos)
{
	Position = Pos;
	UpdateMatrix();
}

void Sprite::SetPosition(FLOAT x, FLOAT y)
{
	SetPosition(D3DXVECTOR2(x, y));
}

void Sprite::SetRotation(float radian)
{
	Rotation = radian;
	UpdateMatrix();
}

void Sprite::SetRotation(int degree)
{
	SetRotation(degree * PI / 180);
}

void Sprite::SetScale(D3DXVECTOR2 scale)
{
	Scale = scale;
	UpdateMatrix();
}

void Sprite::SetScale(FLOAT dx, FLOAT dy)
{
	SetScale(D3DXVECTOR2(dx, dy));
}

D3DXMATRIX Sprite::GetMatrix()
{
	return Matrix;
}

D3DXIMAGE_INFO *Sprite::GetInfo()
{
	return &Info;
}

void Sprite::UpdateMatrix()
{
	D3DXMatrixTransformation2D(&Matrix, &CenterRect, 0, &Scale, &CenterRect, Rotation, &D3DXVECTOR2(Position.x - CenterRect.x, Position.y - CenterRect.y));
}

void Sprite::Init(int ID)
{
	Texture *Instance = Texture::GetInstance();

	texture = Instance->GetTexture(ID);
	Info = Instance->GetInfo(ID);

	Position = D3DXVECTOR2(0, 0);
	SetRect(0, Info.Height, 0, Info.Width);
	Scale = D3DXVECTOR2(1, 1);
	Rotation = 0.0f;

	UpdateMatrix();
}
