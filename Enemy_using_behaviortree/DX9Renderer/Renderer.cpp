#include "Renderer.h"

bool CDX9Renderer::Init(HWND hWnd, bool bWindow, int nWindowWidth, int nWindowHeight)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);

	DX9Init(hWnd, bWindow, nWindowWidth, nWindowHeight);
	
	TargetObject();

	camera_ = new CCamera({ 0.0f,0.0f,0.0f }, { 0.0f, 5.0f,-20.0f }, { 0.0f,1.0f,0.0f });
	//light_ = new CLight()
	return true;
}

void CDX9Renderer::Uninit()
{
	if (pD3D_ != NULL)
	{
		pD3D_->Release();
		pD3D_ = NULL;
	}
	if (device_ != NULL)
	{
		device_->Release();
		device_ = NULL;
	}
}

void CDX9Renderer::Update()
{
}

void CDX9Renderer::Draw()
{
	device_->Clear(0,										// RECT構造体配列の矩形の数
		NULL,									// RECT構造体の先頭アドレス(画面全体はNULL)
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),	// TARGETは色のクリア、ZBUFFERはZバッファのクリア
		D3DCOLOR_RGBA(30, 64, 192, 255),		// クリアカラ―(TARGETがあるとき)
		1.0f,									// Zバッファのクリア値
		0);									// ステンシル値のクリア値

	SUCCEEDED(device_->BeginScene());
	
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);

	world = world;
	camera_->CameraUpdate(device_);
	for (auto object : rendererobject_)
	{
		auto  mesh = meshinfo_[object->meshkey_];
	
		device_->SetStreamSource(0, mesh->vertex_buffer, 0, sizeof(VERTEX3D));
		device_->SetIndices(mesh->index_buffer);
		device_->SetTexture(0, textureinfo_["Cube"]->texture);
	}
	device_->SetFVF(FVF_VERTEX3D);
	device_->SetRenderState(D3DRS_LIGHTING, false);
	device_->SetTransform(D3DTS_WORLD, &world);
	device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	//device_->SetStreamSource(0, meshinfo_["Cube"]->vertex_buffer, 0, sizeof(VERTEX3D));
	//device_->SetIndices(meshinfo_["Cube"]->index_buffer);


	device_->EndScene();

	device_->Present(NULL, NULL, NULL, NULL);
}

bool CDX9Renderer::DX9Init(HWND hWnd, bool bWindow, int nWindowWidth, int nWindowHeight)
{
	pD3D_ = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3D_ == NULL)
	{
		MessageBox(hWnd, "Direct3Dインターフェースの取得に失敗しました。", NULL, MB_OK);
		return false;
	}

	D3DDISPLAYMODE d3ddm;

	if (FAILED(pD3D_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		MessageBox(hWnd, "ディスプレイモードの取得に失敗しました。", NULL, MB_OK);
		return false;
	}

	// デバイスのプレゼンテーションパラメータ(デバイスを作成するためのデータ)
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));							//　中のものを全てを初期化する(初期化する先頭アドレス, 初期化するサイズ)
	d3dpp.BackBufferWidth = nWindowWidth;				//　裏画面(バックバッファ)の幅
	d3dpp.BackBufferHeight = nWindowHeight;				//	裏画面(バックバッファ)の高さ
	d3dpp.BackBufferFormat = d3ddm.Format;				//	色数
	d3dpp.BackBufferCount = 1;							//	バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//	映像信号の同期(DISCARDは垂直同期を気にする)
	d3dpp.EnableAutoDepthStencil = TRUE;						//	TRUEで良い
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//	今はこれで良い上のフォーマット
	d3dpp.Windowed = bWindow;						//	TRUEでウィンドウモード,FALSEでフルスクリーンモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//	フルスクリーンモードの時のリフレッシュレートのHz数を変更
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//	モニターのHz数に合わせて描画される(IMMEDIATEだと垂直同期を待たずに描画する)

	if (FAILED(pD3D_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&device_
	)))
	{
		MessageBox(hWnd, "Direct3DDeviceの作成に失敗しました", "エラー", MB_OK);
		return false;
	}
	device_->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	
	return true;
}

void CDX9Renderer::TargetObject()
{
	auto &Cube = meshinfo_["Cube"];
	Cube = new MeshInfomation;
	HRESULT hr;

	auto &SetTexture = textureinfo_["Cube"];
	SetTexture = new Textureinfomation;
	hr = D3DXCreateTextureFromFile(device_, Texturers::Texture2D.c_str(), &SetTexture->texture);

	if (FAILED(hr))
	{
		MessageBox(NULL, "頂点バッファが作れなかった", "ERROR", MB_OK);
	}


	hr = device_->CreateVertexBuffer(
		sizeof(VERTEX3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX3D,
		D3DPOOL_MANAGED,
		&Cube->vertex_buffer,
		NULL
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "頂点バッファが作れませんでした", "エラー", MB_OK);
		PostQuitMessage(0);
	}

	VERTEX3D* pV;
	Cube->vertex_buffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);

	VERTEX3D v[4] =
	{
		{ { 10.0f,-5.0f, 0.0f },{ 0.0f,1.0f,0.0f }, D3DCOLOR(D3DCOLOR_RGBA(255,255,255,255)),{ 0.0f,0.0f } },
		{ { 10.0f,5.0f, 0.0f },{ 0.0f,1.0f,0.0f }, D3DCOLOR(D3DCOLOR_RGBA(255,255,255,255)),{ 1.0f,0.0f } },
		{ { -10.0f,5.0f, 0.0f },{ 0.0f,1.0f,0.0f }, D3DCOLOR(D3DCOLOR_RGBA(255,255,255,255)),{ 1.0f,1.0f } },
		{ { -10.0f,-5.0f, 0.0f },{ 0.0f,1.0f,0.0f }, D3DCOLOR(D3DCOLOR_RGBA(255,255,255,255)),{ 1.0f,0.0f } },
	};

	memcpy(&pV[0], &v[0], sizeof(VERTEX3D) * 4);

	Cube->vertex_buffer->Unlock();

	hr = device_->CreateIndexBuffer
	(
		sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&Cube->index_buffer,
		NULL
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "インデックスバッファが作れませんでした。", "エラー", MB_OK);
		PostQuitMessage(0);
	}

	LPWORD pIndex;
	Cube->index_buffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);

	WORD index[] =
	{
		0,3,2,
		2,1,0,
	};

	object = new RenderObject("Cube");
	rendererobject_.emplace_back(object);
	memcpy(&pIndex[0], &index[0], sizeof(WORD) * 6);
	Cube->index_buffer->Unlock();
}
