//=============================================================================
//
// �|�C���^�[�̏���[pointer.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
#include "renderer.h"
#include "pointer.h"
#include "enemy.h"
#include "explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"
#include "effect.h"
#include "player.h"
#include "input.h"
#include "gamepad.h"

LPDIRECT3DTEXTURE9 CPointer::m_pTexturePointer = 0;

//=============================================================================
//�}�N����`
//=============================================================================
#define HITSIZE_X (200)
#define HITSIZE_Y (200)
#define ROLL_SPEED (0.03f)

//=============================================================================
//�����X�g���N�^
//=============================================================================
CPointer::CPointer(OBJECT_TYPE type = OBJECT_TYPE_POINTER) : CScene2D(type)
{
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPointer::~CPointer()
{

}

//=============================================================================
// �N���G�C�g
//=============================================================================
CPointer *CPointer::Create()
{
	CPointer *pPointer;
	pPointer = new CPointer(OBJECT_TYPE_POINTER);
	pPointer->Init();
	pPointer->BindTexture(m_pTexturePointer);
	return pPointer;
}

//=============================================================================
// ����������
//=============================================================================
void CPointer::Init()
{
	CScene2D::Init();
	//PointRot = 0.0f;
	//SetRot(PointRot);
	// �|�W�V�����̎擾
	CPlayer *pPlayer = CPlayer::GetPlayer();
	m_Playerpos = pPlayer->GetPosition();
	PointRot = D3DX_PI * 1.0f;
	SetRot(PointRot);

	SetObjType(CScene::OBJECT_TYPE_POINTER);
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CPointer::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �|���S���X�V����
//=============================================================================
void CPointer::Update(void)
{
	// �L�[�{�[�h�̎擾
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̎擾
	CGamepad *pGamepad = CManager::GetGamePad();

	//�T�C�Y�ݒ�
	SetSize(60.0f, 60.0f);
	// �v���C���[�̎擾
	CPlayer *pPlayer = CPlayer::GetPlayer();

	m_Playerpos = pPlayer->GetPosition();//�v���C���[�̃|�W�V�������擾
	
	m_Playerpos += D3DXVECTOR3(sinf(PointRot) * 100, cosf(PointRot) * 100, 0.0f);//�v���C���[���班�����ꂽ�ʒu�Ƀ|�C���^�[��z�u

	//�v���C���[�̈ʒu�𒆐S�Ƃ��ĉ�]����
	if (pInputKeyborad->GetKeyboardPress(DIK_RIGHT))
	{//�E
		RotSet(0.5f);
		if ( pInputKeyborad->GetKeyboardPress(DIK_UP))
		{//�E��
			RotSet(0.75f);
		}
		else if ( pInputKeyborad->GetKeyboardPress(DIK_DOWN))
		{//�E��
			RotSet(0.25f);
		}
	}
	else if (pInputKeyborad->GetKeyboardPress(DIK_LEFT))
	{//��
		RotSet(-0.5f);

		if (pInputKeyborad->GetKeyboardPress(DIK_UP))
		{//����
			RotSet(-0.75f);
		}
		else if (pInputKeyborad->GetKeyboardPress(DIK_DOWN))
		{//����
			RotSet(-0.25f);
		}
	}
	else if (pInputKeyborad->GetKeyboardPress(DIK_UP))
	{//��
		RotSet(1.0f);
	}

	else if (pInputKeyborad->GetKeyboardPress(DIK_DOWN))
	{//��
		RotSet(0.0f);
	}

	else if (pInputKeyborad->GetKeyboardPress(DIK_E))
	{//�E�ɖ�󂪈ړ�����
		m_Playerpos -= D3DXVECTOR3(sinf(D3DX_PI*ROLL_SPEED), cosf(D3DX_PI*ROLL_SPEED), 0.0f);
		PointRot -= D3DX_PI * ROLL_SPEED;
		pPlayer->SetAttackRot(PointRot);//PointRot���v���C���[�̍U�������Ɏw��
		SetRot(PointRot);				//PointRot�̕����Ƀe�N�X�`������]
	}

	else if (pInputKeyborad->GetKeyboardPress(DIK_Q))
	{//���ɖ�󂪈ړ�����
		m_Playerpos += D3DXVECTOR3(sinf(D3DX_PI*ROLL_SPEED), cosf(D3DX_PI*ROLL_SPEED), 0.0f);
		PointRot += D3DX_PI * ROLL_SPEED;
		pPlayer->SetAttackRot(PointRot);//PointRot���v���C���[�̍U�������Ɏw��
		SetRot(PointRot);				//PointRot�̕����Ƀe�N�X�`������]
	}

	//-------------------------------------------------
	float Stick_X, Stick_Y;
	pGamepad->GetStickRight(0, &Stick_X, &Stick_Y);		//�E�X�e�B�b�N��X��Y���擾���Ă���
	if (fabsf(Stick_X) >= 3000 ||fabsf(Stick_Y) >= 3000)
	{// ����Βl�Ƃ��Čv�Z(3000��-3000�ǂ�����)
		PointRot = atan2f(Stick_X, -Stick_Y);
		//			����̓_�̊p�x�����߂Ă����
		pPlayer->SetAttackRot(PointRot);
		SetRot(PointRot);
	}
	//-------------------------------------------------
	SetPosition(m_Playerpos);

	CScene2D::Update();

}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CPointer::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// �p�x�ݒ�
//=============================================================================
void CPointer::RotSet(float fRot)
{
	// �|�W�V�����̎擾
	CPlayer *pPlayer = CPlayer::GetPlayer();
	m_Playerpos += D3DXVECTOR3(sinf(D3DX_PI*fRot), cosf(-D3DX_PI*fRot), 0.0f);
	PointRot = D3DX_PI * fRot;
	pPlayer->SetAttackRot(PointRot);
	SetRot(PointRot);
}
//=============================================================================
// ���[�h
//=============================================================================
HRESULT CPointer::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/pointer.png", &m_pTexturePointer);
	return S_OK;
}
//=============================================================================
// �A�����[�h
//=============================================================================
void CPointer::Unload(void)
{

	if (m_pTexturePointer != NULL)
	{
		m_pTexturePointer -> Release();
		m_pTexturePointer = NULL;
	}
}
