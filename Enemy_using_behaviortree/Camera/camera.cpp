#include "camera.h"
#include "../Input/Input.h"
#include "../main.h"
/*
�J�����ɋ��̔�����������ăv���C���[�����̋�����o�����ɂȂ�����A�J������Ǐ]������悤�ɂ���B
*/
D3DXMATRIX CCamera::m_GetView_;
D3DXMATRIX CCamera::m_GetProj_;

CCamera::~CCamera()
{
}

void CCamera::CameraUpdate(LPDIRECT3DDEVICE9 device)
{
	constexpr float SPEED = 0.1f;

	D3DXMATRIX CameraRotation;
	D3DXMatrixIdentity(&CameraRotation);
	//CInputKeyboard* pInputKeyboard = new;
	//
	//if (pInputKeyboard->GetKeyPress(DIK_RIGHT))
	//{
	//	rotation_ = D3DXToRadian(0.78f) * D3DX_PI;
	//	D3DXMatrixRotationY(&CameraRotation, rotation_);
	//}
	//if (pInputKeyboard->GetKeyPress(DIK_LEFT))
	//{
	//	rotation_ = D3DXToRadian(-0.78f) * D3DX_PI;
	//	D3DXMatrixRotationY(&CameraRotation, rotation_);
	//}

	D3DXVec3TransformCoord(&offset, &offset, &CameraRotation);
	D3DXVec3TransformCoord(&eye_, &eye_, &CameraRotation);
	D3DXVec3TransformCoord(&at_, &at_, &CameraRotation);

	//�r���[�s��̍쐬
	D3DXMatrixLookAtLH(
		&this->matrix_view,
		&this->eye_,
		&this->at_,
		&this->up_
	);

	//�v���W�F�N�V�����s��̍쐬
	D3DXMatrixPerspectiveFovLH(&this->matrix_projection, D3DX_PI / 3 /*D3DXToRadian(60),*/, (float)wiindows_rect::SCREEN_WIDTH / wiindows_rect::SCREEN_HEIGHT, 0.1f, 10000.0f);

	//�e��ލs��̐ݒ�
	device->SetTransform(D3DTS_VIEW, &this->matrix_view);
	device->SetTransform(D3DTS_PROJECTION, &this->matrix_projection);

	this->m_GetView_ = this->matrix_view;
	this->m_GetProj_ = this->matrix_projection;
}

D3DXMATRIX CCamera::SetView()
{
	return m_GetView_;
}

D3DXMATRIX CCamera::SetProj()
{
	return m_GetProj_;
}
