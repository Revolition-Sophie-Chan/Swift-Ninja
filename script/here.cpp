//=============================================================================
//
// �|�C���^�[�̏���[Here.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "renderer.h"
#include "here.h"
#include "enemy.h"
#include "explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"
#include "effect.h"
#include "player.h"
#include "input.h"
#include "gamepad.h"
#include "texture.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CHere::m_pTextureHere=NULL;

//=============================================================================
//�}�N����`
//=============================================================================
#define HITSIZE_X (200)
#define HITSIZE_Y (200)
#define ROLL_SPEED (0.03f)

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CHere::CHere(OBJECT_TYPE type = OBJECT_TYPE_POINTER) : CScene2D(type)
{
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CHere::~CHere()
{

}

//=============================================================================
// �N���G�C�g
//=============================================================================
CHere *CHere::Create()
{
	CHere *pHere;
	pHere = new CHere(OBJECT_TYPE_POINTER);
	pHere->Init();
	pHere->BindTexture(m_pTextureHere);
	return pHere;
}

//=============================================================================
// ����������
//=============================================================================
void CHere::Init()
{

	bHere = false;
	CScene2D::Init();
	// �|�W�V�����̎擾
	CPlayer *pPlayer = CPlayer::GetPlayer();
	m_Playerpos = pPlayer->GetPosition();

	SetObjType(CScene::OBJECT_TYPE_POINTER);
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CHere::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �|���S���X�V����
//=============================================================================
void CHere::Update(void)
{


	CScene2D::Update();

	// �L�[�{�[�h�̎擾
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	// �L�[�{�[�h�̎擾
	CGamepad *pGamepad = CManager::GetGamePad();

	//�T�C�Y�ݒ�
	SetSize(60.0f, 60.0f);
	// �v���C���[�̎擾
	CPlayer *pPlayer = CPlayer::GetPlayer();

	m_Playerpos = pPlayer->GetPosition();//�v���C���[�̃|�W�V�������擾

	if (m_Playerpos.y <= 0.0f)
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		bHere = true;
	}
	else
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	SetPosition(D3DXVECTOR3(m_Playerpos.x,50.0f,0.0f));

}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CHere::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// ���[�h
//=============================================================================
HRESULT CHere::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Here.png", &m_pTextureHere);
	return S_OK;
}
//=============================================================================
// �A�����[�h
//=============================================================================
void CHere::Unload(void)
{

		if (m_pTextureHere != NULL)
		{
			m_pTextureHere->Release();
			m_pTextureHere = NULL;
		}

}
