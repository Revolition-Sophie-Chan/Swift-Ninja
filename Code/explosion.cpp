//=============================================================================
//
// �����̏���[explosion.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "renderer.h"
#include "explosion.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTextureExplosion[EXPLOSIONTYPE_MAX] = {};

//=============================================================================
//�}�N����`
//=============================================================================
#define EXPLOSION_ANIM		(3)	//�A�j���[�V�����̑���
#define JUMPEXPLOSION_ANIM	(4)	//�A�j���[�V�����̑���

//============================================================================================
//�R���X�g���N�^
//============================================================================================
CExplosion::CExplosion(OBJECT_TYPE type = OBJECT_TYPE_EXPLOSION) : CScene2D(type)
{
}
//============================================================================================
//�f�X�g���N�^
//============================================================================================
CExplosion::~CExplosion()
{
}

//=============================================================================
//��������
//=============================================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 EPpos,int nLife,int nCount, EXPLOSIONTYPE nType)
{
	CExplosion *pExplosion;
	pExplosion = new CExplosion(OBJECT_TYPE_EXPLOSION);
	pExplosion->ExplosionType = nType;
	pExplosion->SetPosition(EPpos);
	pExplosion->SetLife(nLife);
	pExplosion->Init();
	pExplosion->InitTex(nCount, 1.0f);
	pExplosion->BindTexture(m_pTextureExplosion[nType]);
	return pExplosion;
}

//=============================================================================
//�����̎�ގ擾
//=============================================================================
CExplosion::EXPLOSIONTYPE CExplosion::GetType()
{
	return ExplosionType;
}

//=============================================================================
//����������
//=============================================================================
void CExplosion::Init()
{
	CScene2D::Init();

	m_nLife = CScene2D::GetLife();
	nCountExplosionAnim		= 0;
	nPattenExplosionAnim	= 0;
}

//=============================================================================
//�I������
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
//�����X�V����
//=============================================================================
void CExplosion::Update(void)
{
	// �|�W�V�����̎擾
	D3DXVECTOR3 pos = GetPosition();
	m_nLife--;
	nCountExplosionAnim++;

	//�����̃^�C�v�ɂ���ăT�C�Y��A�j���[�V������ς���
	TypeManager();

	CScene2D::Update();
}

//=============================================================================
//�`��
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
//���[�h
//=============================================================================
HRESULT CExplosion::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/Texture/explosion001.png", &m_pTextureExplosion[EXPLOSIONTYPE_ENEMY]);
	D3DXCreateTextureFromFile(pDevice, "Data/Texture/jump_effect.png", &m_pTextureExplosion[EXPLOSIONTYPE_JUMP]);

	return S_OK;
}

//=============================================================================
//�A�����[�h
//=============================================================================
void CExplosion::Unload(void)
{
	for (int nCnt = 0; nCnt < EXPLOSIONTYPE_MAX; nCnt++)
	{
		if (m_pTextureExplosion[nCnt] != NULL)
		{
			m_pTextureExplosion[nCnt]->Release();
			m_pTextureExplosion[nCnt] = NULL;
		}
	}
}

//=============================================================================
//�����X�V����
//=============================================================================
void CExplosion::TypeManager(void)
{
	switch (ExplosionType)
	{
		//�G������
	case EXPLOSIONTYPE_ENEMY:
		SetSize(80.0f, 80.0f);
		if (nCountExplosionAnim % EXPLOSION_ANIM == 0)
		{
			nPattenExplosionAnim = (nPattenExplosionAnim + 1) % 16;
			SetAnim(16, nPattenExplosionAnim, 2);
			if (nCountExplosionAnim / EXPLOSION_ANIM == 16)
			{
				Release();
			}
		}
		break;

		//��i�W�����v���̃G�t�F�N�g
	case EXPLOSIONTYPE_JUMP:
		SetSize(60.0f, 60.0f);
		if (nCountExplosionAnim % JUMPEXPLOSION_ANIM == 0)
		{
			nPattenExplosionAnim = (nPattenExplosionAnim + 1) % 4;
			SetAnim(4, nPattenExplosionAnim, 2);
			if (nCountExplosionAnim / JUMPEXPLOSION_ANIM == 4)
			{
				Release();
			}
		}
		break;
	}
}

