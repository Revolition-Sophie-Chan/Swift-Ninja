//=========================================================================
//
// ゲージ処理 [gauge.cpp]
// Author : tanaka rikiya
//
//=========================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "gauge.h"
#include "player.h"
#include "enemy.h"
#include "manager.h"
#include "renderer.h"

//=========================================================================
// マクロ定義 
//========================================================================= 
#define GAUGE_NAME "Data/Texture/fade.png"

//=========================================================================
// 静的メンバ変数の初期化 
//=========================================================================
LPDIRECT3DTEXTURE9 CGauge::m_pTextureGauge[UITYPE_MAX] = {};

//=========================================================================
// 初期化処理
//=========================================================================
CGauge::CGauge(OBJECT_TYPE type = OBJECT_TYPE_GAUGE) : CScene2D(type)
{
}

//=========================================================================
// 終了処理
//=========================================================================
CGauge::~CGauge()
{
}

//=========================================================================
// テクスチャの読み込み
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
// テクスチャの開放
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
// 生成処理
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
// 初期化処理
//=========================================================================
void CGauge::Init(float fWight, float fHeight)
{
	CScene2D::Init();
	// 初期化
	m_fWigth = fWight;
	m_fHeight = fHeight;
	nFeverCount = 0;
	nFeverTime = 0;
	nCountTexture = 0;
	m_MaxGauge = 0;
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJECT_TYPE_GAUGE);

}

//=========================================================================
// 終了処理
//=========================================================================
void CGauge::Uninit(void)
{
	CScene2D::Uninit();
}

//=========================================================================
// 更新処理
//=========================================================================
void CGauge::Update(void)
{
	CScene2D::Update();

	// HPの管理
	HPManager();
}

//=========================================================================
// 描画処理
//=========================================================================
void CGauge::Draw(void)
{
	CScene2D::Draw();
}

//=========================================================================
// HPの管理
//=========================================================================
void CGauge::HPManager(void)
{
	nCountTexture++;
	CPlayer *pPlayer = CPlayer::GetPlayer();
	for (int nCntPri = 0; nCntPri < 20; nCntPri++)
	{
		for (int nCntScene = 0; nCntScene < MAX_TEXTURE; nCntScene++)
		{
			// シーン情報を取得
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
// UIの種類を取得
//=========================================================================
CGauge::GAUGETYPE CGauge::GetGaugeType(void)
{
	return m_nType;
}