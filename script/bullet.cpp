//=============================================================================
//
// �e�̏���[bullet.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
#include "renderer.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "inputkeyboard.h"
#include "Scene2D.h"
#include "effect.h"
#include "particle.h"

LPDIRECT3DTEXTURE9 CBullet::m_pTextureBullet[MAX_TEXTURE] = {};
//=============================================================================
//�����X�g���N�^
//=============================================================================
CBullet::CBullet(OBJECT_TYPE type = OBJECT_TYPE_EXPLOSION) : CScene2D(type)
{
	m_pTextureBullet[MAX_TEXTURE] = {};//�e�N�X�`���ւ̃|�C���^
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// �N���G�C�g
//=============================================================================
CBullet *CBullet::Create()
{
	CBullet *pBullet;
	pBullet = new CBullet(OBJECT_TYPE_EXPLOSION);
	pBullet->Init();
	pBullet->BindTexture(m_pTextureBullet[0]);
	return pBullet;
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CBullet::CollisionTest(D3DXVECTOR3 pos)
{
	for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
	{
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene, OBJECT_TYPE_ENEMY);
		if (pScene != NULL)
		{
			CScene::OBJECT_TYPE objType;

			objType = pScene->GetObjType();

			if (objType == CScene::OBJECT_TYPE_ENEMY)
			{
				D3DXVECTOR3 EnemyPos = ((CEnemy*)pScene)->GetEnemyPos();
				if (EnemyPos.x + HITSIZE_X / 2 >= pos.x &&
					EnemyPos.x - HITSIZE_X / 2 <= pos.x &&
					EnemyPos.y + HITSIZE_Y / 2 >= pos.y &&
					EnemyPos.y - HITSIZE_Y / 2 <= pos.y)
				{
					CExplosion *pExplosion = CExplosion::Create(EnemyPos);
					pExplosion->SetPosition(pos);
					pScene->Release();
				}
			}
		}
	}
	return false;
}

//=============================================================================
// �G�t�F�N�g�̍쐬
//=============================================================================
void CBullet::MakeEffect(void)
{
	D3DXVECTOR3 pos = GetPosition();
	D3DXCOLOR col = GetColor();
	// �G�t�F�N�g�̐���
	CEffect *pEffect = CEffect::Create(pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 0, 100);
	pEffect->SetPosition(pos);
	pEffect->SetColor(col);
	//pEffect->SetSize();
}

//=============================================================================
//�@�����̍쐬
//=============================================================================
void CBullet::MakeExplosion(void)
{
	D3DXVECTOR3 pos = GetPosition();
	// �����̐���
	CExplosion *pExplosion = CExplosion::Create(pos);
	pExplosion->SetPosition(pos);
}

//=============================================================================
// ����������
//=============================================================================
void CBullet::Init()
{
	CScene2D::Init();
	SetObjType(CScene::OBJECT_TYPE_EXPLOSION);
	m_nLife = 100;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// polygon�X�V����
//=============================================================================
void CBullet::Update(void)
{	
	// �|�W�V�����̎擾
	D3DXVECTOR3 pos = GetPosition();

	// �G�t�F�N�g�̍쐬
	MakeEffect();

	// �ړ�����
	m_move.y -= 0.5f;
	pos += m_move;

	// �|�W�V�����̍X�V
	SetPosition(pos);
	CScene2D::Update();

	// ���C�t���f�N�������g
	m_nLife--;
	if (m_nLife <= 0)
	{// �����̍쐬
		MakeExplosion();
		// �J������
		Release();
	}

	// �����蔻��
	CollisionTest(pos);
}
//=============================================================================
// �|���S���̕`��
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// ���[�h
//=============================================================================
HRESULT CBullet::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "Data/KSTW.png", &m_pTextureBullet[0]);
	return S_OK;
}
//=============================================================================
// �A�����[�h
//=============================================================================
void CBullet::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_pTextureBullet[nCnt] != NULL)
		{
			m_pTextureBullet[nCnt]->Release();
			m_pTextureBullet[nCnt] = NULL;
		}
	}

}

