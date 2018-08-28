#pragma once
//インクルード
#include "../main.h"

class CRenderer
{
public:
	CRenderer(){}
	~CRenderer(){}
public:
	bool Init(HWND hWnd, bool bWindow, int nWindowWidth, int nWindowHeight);
	void Uninit();
	bool Draw();
private:
	LPDIRECT3DDEVICE9 GetDevice();
};