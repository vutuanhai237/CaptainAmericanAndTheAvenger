#pragma once
#include <d3dx9.h>
#include <vector>

class Texture
{
public:
	static Texture* GetInstance();
	HRESULT Add(int &ID, LPCWSTR path, D3DCOLOR TransparentColor);
	LPDIRECT3DTEXTURE9 GetTexture(int ID);
	D3DXIMAGE_INFO GetInfo(int ID);
	void Release();
private:
	Texture() {};
	~Texture();

	std::vector<D3DXIMAGE_INFO> Info;
	std::vector<LPDIRECT3DTEXTURE9> Textures;
	static Texture* Instance;
};