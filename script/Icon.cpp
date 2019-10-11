//=============================================================================
//
// �A�C�R���̏���[Icon.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
#include "renderer.h"
#include "Icon.h"
#include "enemy.h"
#include "explosion.h"
#include "inputkeyboard.h"
#include "scene2D.h"
#include "effect.h"
#include "player.h"
#include "input.h"

LPDIRECT3DTEXTURE9 CIcon::m_pTextureIcon= {};
//=============================================================================
//�����X�g���N�^
//=============================================================================
CIcon::CIcon(OBJECT_TYPE type = OBJECT_TYPE_UI) : CScene2D(type)
{
	//m_pTextureIcon[MAX_TEXTURE] = {};//�e�N�X�`���ւ̃|�C���^
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CIcon::~CIcon()
{

}

//=============================================================================
// �N���G�C�g
//=============================================================================
CIcon *CIcon::Create(D3DXVECTOR3 Iconpos)
{
	CIcon *pIcon;
	pIcon = new CIcon(OBJECT_TYPE_UI);
	pIcon->Init();
	pIcon->SetPosition(Iconpos);
	pIcon->BindTexture(m_pTextureIcon);
	return pIcon;
}

//=============================================================================
// ����������
//=============================================================================
void CIcon::Init()
{
	CScene2D::Init();
	bFlag = true;
	SetObjType(CScene::OBJECT_TYPE_UI);
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CIcon::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �|���S���X�V����
//=============================================================================
void CIcon::Update(void)
{
	//�T�C�Y�ݒ�
	SetSize(70.0f, 70.0f);

	// �L�[�{�[�h�̎擾
	CInputkeyborad *pInputKeyborad = CManager::GetInputKeyboard();

	//�v���C���[�̎擾
	CPlayer *pPlayer = CPlayer::GetPlayer();

	bFlag = pPlayer->GetPlayerAttackFlag();

	if (bFlag == true)
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	else
	{
		SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f));
	}
	CScene2D::Update();
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CIcon::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// ���[�h
//=============================================================================
HRESULT CIcon::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/Ability_Icon.png", &m_pTextureIcon);
	return S_OK;
}
//=============================================================================
// �A�����[�h
//=============================================================================
void CIcon::Unload(void)
{
	if (m_pTextureIcon != NULL)
	{
		m_pTextureIcon->Release();
		m_pTextureIcon = NULL;
	}
}

