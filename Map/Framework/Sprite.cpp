#include "Sprite.h"
#include "Texture.h"
#include "d3d.h"

Sprite::Sprite(int ID)
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

Sprite::Sprite(LPCWSTR Path, D3DXCOLOR TransparentColor)
{
	int ID;
	Texture::GetInstance()->Add(ID, Path, TransparentColor);
	Sprite::Sprite(ID);
}

void Sprite::Draw()
{
	LPD3DXSPRITE Hander = d3d::GetInstance()->GetSpriteHander();
	D3DXMATRIX OldMatrix;
	Hander->GetTransform(&OldMatrix);
	Hander->SetTransform(&Matrix);

	Hander->Begin(D3DXSPRITE_ALPHABLEND);
	Hander->Draw(texture, &rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	Hander->End();

	Hander->SetTransform(&OldMatrix);
}

void Sprite::SetRect(RECT Rect)
{
	rect.top = Rect.top;
	rect.bottom = Rect.bottom;
	rect.left = Rect.left;
	rect.right = Rect.right;

	CenterRect.x = (Rect.right - Rect.left) / 2;
	CenterRect.y = (Rect.bottom - Rect.top) / 2;

	UpdateMatrix();
}

void Sprite::SetRect(LONG top, LONG bottom, LONG left, LONG right)
{
	rect.top = top;
	rect.bottom = bottom;
	rect.left = left;
	rect.right = right;

	CenterRect.x = (right - left) / 2;
	CenterRect.y = (bottom - top) / 2;

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
	SetRotation(degree * 3.14159f / 180);
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

void Sprite::UpdateMatrix()
{
	D3DXMatrixTransformation2D(&Matrix, &CenterRect, 0, &Scale, &CenterRect, Rotation, &D3DXVECTOR2(Position.x - CenterRect.x, Position.y - CenterRect.y));
}
