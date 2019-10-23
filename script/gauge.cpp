//=========================================================================
//
// �Q�[�W���� [gauge.cpp]
// Author : tanaka rikiya
//
//=========================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "gauge.h"
#include "player.h"
#include "enemy.h"
#include "manager.h"
#include "renderer.h"

//=========================================================================
// �}�N����` 
//========================================================================= 
#define GAUGE_NAME "Data/Texture/fade.png"

//=========================================================================
// �ÓI�����o�ϐ��̏����� 
//=========================================================================
LPDIRECT3DTEXTURE9 CGauge::m_pTextureGauge[UITYPE_MAX] = {};

//=========================================================================
// ����������
//=========================================================================
CGauge::CGauge(OBJECT_TYPE type = OBJECT_TYPE_GAUGE) : CScene2D(type)
{
}

//=========================================================================
// �I������
//=========================================================================
CGauge::~CGauge()
{
}

//=========================================================================
// �e�N�X�`���̓ǂݍ���
//=========================================================================
void CGauge::Load(void)
{	
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXCreateTextureFromFile(pDevice, GAUGE_NAME, &m_pTextureGauge[UITYPE_FEVER]);
	D3DXCreateTextureFromFile(pDevice, GAUGE_NAME, &m_pTextureGauge[UITYPE_HP]);
	D3DXCreateTextureFromFile(pDevice, GAUGE_NAME, &m_pTextureGauge[UITYPE_FEVERMAX]);
	D3DXCreateTextureFromFile(pDevice, GAUGE_NAME, &m_pTextureGauge[UITYPE_HPMAX]);

}

//=========================================================================
// �e�N�X�`���̊J��
//=========================================================================
void CGauge::Unload(void)
{	
	for (int nCnt = 0; nCnt < UITYPE_MAX; nCnt++)
	{
		if (m_pTextureGauge[nCnt] != NULL)
		{
			m_pTextureGauge[nCnt]->Release();
			m_pTextureGauge[nCnt] = NULL;
		}
	}
}

//=========================================================================
// ��������
//=========================================================================
CGauge *CGauge::Create(D3DXVECTOR3 pos, D3DXCOLOR col,float fWight, float fHeight, GAUGETYPE nType)
{
	CGauge *pGauge;
	pGauge = new CGauge;

	pGauge->m_nType = nType;
	pGauge->SetPosition(pos);
	pGauge->SetColor(col);
	pGauge->Init(fWight,fHeight);
	pGauge->InitTex(1, 1.0f);
	pGauge->BindTexture(m_pTextureGauge[nType]);

	return pGauge;
}

//=========================================================================
// ����������
//=========================================================================
void CGauge::Init(float fWight, float fHeight)
{
	CScene2D::Init();
	// ������
	m_fWigth = fWight;
	m_fHeight = fHeight;
	nFeverCount = 0;
	nFeverTime = 0;
	nCountTexture = 0;
	m_MaxGauge = 0;
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJECT_TYPE_GAUGE);

}

//=========================================================================
// �I������
//=========================================================================
void CGauge::Uninit(void)
{
	CScene2D::Uninit();
}

//=========================================================================
// �X�V����
//=========================================================================
void CGauge::Update(void)
{
	CScene2D::Update();

	// HP�̊Ǘ�
	HPManager();
}

//=========================================================================
// �`�揈��
//=========================================================================
void CGauge::Draw(void)
{
	CScene2D::Draw();
}

//=========================================================================
// HP�̊Ǘ�
//=========================================================================
void CGauge::HPManager(void)
{
	nCountTexture++;
	CPlayer *pPlayer = CPlayer::GetPlayer();
	for (int nCntPri = 0; nCntPri < 20; nCntPri++)
	{
		for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
		{
			// �V�[�������擾
			CScene *pScene = CScene::GetScene(nCntPri, OBJECT_TYPE_PLAYER);

			if (pScene != NULL)
			{
				CScene::OBJECT_TYPE objType;
				objType = pScene->GetObjType();

				if (m_nType == UITYPE_FEVER)
				{
					if (objType == OBJECT_TYPE_PLAYER)
					{
							
						if (pPlayer->bFever == true)
						{
							SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
							nFeverTime -= 0.000121f;
							SetGauge(m_fWigth*nFeverTime, m_fHeight);
						}
						else
						{
							SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
							nFeverTime = 30.0f;
							nFeverCount = pPlayer->nFever;
							SetGauge(m_fWigth*nFeverCount, m_fHeight);
						}

						//if (nLife < 1)
						//{
						//	bLive = true;
						//}
					}
				}
				if (m_nType == UITYPE_FEVERMAX)
				{
					if (objType == OBJECT_TYPE_PLAYER)
					{
						m_MaxGauge = 30;
						SetGauge(m_fWigth*m_MaxGauge, m_fHeight);
					}
				}


				if (m_nType == UITYPE_HP)
				{

					if (objType == OBJECT_TYPE_PLAYER)
					{
						nLife = ((CPlayer*)pScene)->GetLife();
						if (nLife <= 2)
						{
							if (nCountTexture % 10 == 0 && nCountTexture % 20 != 0)
							{
								SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));
							}
							if (nCountTexture % 20 == 0)
							{
								SetColor(D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f));
							}
						}
						else
						{
							SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						}
						SetGauge(m_fWigth*nLife, m_fHeight);
					}
				}
				if (m_nType == UITYPE_HPMAX)
				{
					if (objType == OBJECT_TYPE_PLAYER)
					{
						m_MaxGauge = 6;
						SetGauge(m_fWigth*m_MaxGauge, m_fHeight);
					}
				}

			}
		}
	}
}

//=========================================================================
// UI�̎�ނ��擾
//=========================================================================
CGauge::GAUGETYPE CGauge::GetGaugeType(void)
{
	return m_nType;
}