#pragma once
#include <d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
class CLight
{
private:
	D3DLIGHT9 settinglight_;
	D3DLIGHT9    light;
	D3DXCOLOR color_ = { 0.3f, 0.3f, 0.3f, 0.3f };
public:
	CLight()
	{
		ZeroMemory(&light, sizeof(D3DLIGHT9));
		light.Diffuse.r = 1.0f;
		light.Diffuse.g = 1.0f;
		light.Diffuse.b = 1.0f;
		light.Direction = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	~CLight() {}
public:
	void light_Init(LPDIRECT3DDEVICE9 device);
	void light_Uninit() {};
	void light_Draw() {};
	void light_Update() {};
	void MaterialSetLight(D3DMATERIAL9 mat, LPDIRECT3DDEVICE9 device);
	void LightSet(D3DLIGHT9 light, LPDIRECT3DDEVICE9 device);

};