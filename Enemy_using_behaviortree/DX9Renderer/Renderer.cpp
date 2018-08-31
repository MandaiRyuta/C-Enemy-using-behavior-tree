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
	device_->Clear(0,										// RECT�\���̔z��̋�`�̐�
		NULL,									// RECT�\���̂̐擪�A�h���X(��ʑS�̂�NULL)
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),	// TARGET�͐F�̃N���A�AZBUFFER��Z�o�b�t�@�̃N���A
		D3DCOLOR_RGBA(30, 64, 192, 255),		// �N���A�J���\(TARGET������Ƃ�)
		1.0f,									// Z�o�b�t�@�̃N���A�l
		0);									// �X�e���V���l�̃N���A�l

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
		MessageBox(hWnd, "Direct3D�C���^�[�t�F�[�X�̎擾�Ɏ��s���܂����B", NULL, MB_OK);
		return false;
	}

	D3DDISPLAYMODE d3ddm;

	if (FAILED(pD3D_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		MessageBox(hWnd, "�f�B�X�v���C���[�h�̎擾�Ɏ��s���܂����B", NULL, MB_OK);
		return false;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^(�f�o�C�X���쐬���邽�߂̃f�[�^)
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));							//�@���̂��̂�S�Ă�����������(����������擪�A�h���X, ����������T�C�Y)
	d3dpp.BackBufferWidth = nWindowWidth;				//�@�����(�o�b�N�o�b�t�@)�̕�
	d3dpp.BackBufferHeight = nWindowHeight;				//	�����(�o�b�N�o�b�t�@)�̍���
	d3dpp.BackBufferFormat = d3ddm.Format;				//	�F��
	d3dpp.BackBufferCount = 1;							//	�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//	�f���M���̓���(DISCARD�͐����������C�ɂ���)
	d3dpp.EnableAutoDepthStencil = TRUE;						//	TRUE�ŗǂ�
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//	���͂���ŗǂ���̃t�H�[�}�b�g
	d3dpp.Windowed = bWindow;						//	TRUE�ŃE�B���h�E���[�h,FALSE�Ńt���X�N���[�����[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//	�t���X�N���[�����[�h�̎��̃��t���b�V�����[�g��Hz����ύX
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//	���j�^�[��Hz���ɍ��킹�ĕ`�悳���(IMMEDIATE���Ɛ���������҂����ɕ`�悷��)

	if (FAILED(pD3D_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&device_
	)))
	{
		MessageBox(hWnd, "Direct3DDevice�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
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
		MessageBox(NULL, "���_�o�b�t�@�����Ȃ�����", "ERROR", MB_OK);
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
		MessageBox(NULL, "���_�o�b�t�@�����܂���ł���", "�G���[", MB_OK);
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
		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�����܂���ł����B", "�G���[", MB_OK);
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
