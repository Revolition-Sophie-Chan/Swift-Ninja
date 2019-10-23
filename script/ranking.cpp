//=============================================================================
//
// ランキング処理 [ranking.cpp]
// Author : tanaka rikiya
//
// ============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include <stdio.h>
#include "load.h"
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "renderer.h"
#include "inputkeyboard.h"
#include "texture.h"
#include "player.h"


//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_RANKING		"Data/Texture/number002.png"	// 読み込むテキストファイル名
#define RANKING_SIZE (20)									// ランキングの大きさ
#define RANKING_MAX (5)										// 数値の個数
#define SAVE_FILE_NAME ("Data/text.txt")					// セーブファイル

//=============================================================================
// コンストラクタ
//=============================================================================
CRanking::CRanking(OBJECT_TYPE type = OBJECT_TYPE_UI) : CScene(type)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CRanking::~CRanking()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CRanking::Init(void)
{
	CTexture::Load();
	int nCntRank;
	m_nRNKData = 0;

	CPlayer *pPlayer = CPlayer::GetPlayer();

	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_RankingPos = D3DXVECTOR3(750.0f, 160.0f, 0.0f);
	m_nRanking = 0;
	
	for (nCntRank = 0; nCntRank < RANKING_DATE; nCntRank++)
	{
		m_aRankin[nCntRank].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aRankin[nCntRank].aName[0];
		m_aRankin[nCntRank].nPoint = 0;
	}

	CTexture::Create(D3DXVECTOR3(650.0f, 80.0f, 0.0f), 160, 110, CTexture::TYPE_RANKING);
	CTexture::Create(D3DXVECTOR3(470.0f, 160.0f, 0.0f), 60, 50, CTexture::TYPE_1ST);
	CTexture::Create(D3DXVECTOR3(470.0f, 240.0f, 0.0f), 60, 50, CTexture::TYPE_2ND);
	CTexture::Create(D3DXVECTOR3(470.0f, 320.0f, 0.0f), 60, 50, CTexture::TYPE_3RD);
	CTexture::Create(D3DXVECTOR3(470.0f, 400.0f, 0.0f), 60, 50, CTexture::TYPE_4TH);
	CTexture::Create(D3DXVECTOR3(470.0f, 480.0f, 0.0f), 60, 50, CTexture::TYPE_5TH);
	CTexture::Create(D3DXVECTOR3(200.0f, 580.0f, 0.0f), 100, 90, CTexture::TYPE_BREAK);

	if (CPlayer::bRankScore == true)
	{
		CScore::Create(pPlayer->nScore);
		CTexture::Create(D3DXVECTOR3(1000.0f, 480.0f, 0.0f), 300, 300, CTexture::TYPE_RANKCOUNT);
		CPlayer::bFinish = false;
	}

	
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
		TEXTURE_RANKING,							// ファイルの名前
		&m_pTextureRanking);						// 読み込むメモリー

	// 頂点情報の作成
	MakeVertexRanking(pDevice);

	AddRanking(0, 0);

}

//=============================================================================
// 終了処理
//=============================================================================
void  CRanking::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuffRanking != NULL)
	{
		m_pVtxBuffRanking->Release();
		m_pVtxBuffRanking = NULL;
	}

	// テクスチャの開放
	if (m_pTextureRanking != NULL)
	{
		m_pTextureRanking->Release();
		m_pTextureRanking = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void  CRanking::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void  CRanking::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	int nCntRanking;

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, m_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTextureRanking);

		for (nCntRanking = 0; nCntRanking < RANKING_MAX * RANKING_DATE; nCntRanking++)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntRanking, 2);
		}
}

//=============================================================================
// 頂点の作成
//=============================================================================
void CRanking::MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D *pVtx;			// 頂点情報へのポイント
	int nCntRanking;			// ランキングカウント
	int nCntRankingData;		// ランキングカウント

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANKING_MAX * RANKING_DATE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffRanking, NULL);

	// 頂点情報の設定
	// 頂点データの範囲をロックし、頂点バッファへのポインタ
	m_pVtxBuffRanking->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntRankingData = 0; nCntRankingData < RANKING_DATE; nCntRankingData++)
	{
		for (nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++)
		{
			pVtx[0].pos = D3DXVECTOR3(m_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,	
				m_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData, 0.0f);							// 一つ目の頂点
			pVtx[1].pos = D3DXVECTOR3(m_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				m_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData, 0.0f);							// 二つ目の頂点
			pVtx[2].pos = D3DXVECTOR3(m_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				m_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData + RANKING_SIZE, 0.0f);				// 三つ目の頂点
			pVtx[3].pos = D3DXVECTOR3(m_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				m_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 50) * nCntRankingData + RANKING_SIZE, 0.0f);				// 四つ目の頂点

			pVtx[0].rhw = 1.0f;	// 一つ目の頂点作成
			pVtx[1].rhw = 1.0f;	// 二つ目の頂点作成
			pVtx[2].rhw = 1.0f;	// 三つ目の頂点作成
			pVtx[3].rhw = 1.0f;	// 四つ目の頂点作成

			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 一つ目の色設定
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 二つ目の色設定
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 三つ目の色設定
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 四つ目の色設定

			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);		// 一つ目のテクスチャ
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);		// 二つ目のテクスチャ
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);		// 三つ目のテクスチャ
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);		// 四つ目のテクスチャ

			pVtx += 4;
		}
	}
	// アンロック
	m_pVtxBuffRanking->Unlock();
}

//=============================================================================
// ランキングの変更
//=============================================================================
void CRanking::AddRanking(int nPoint,int nRankingCnt)
{
	VERTEX_2D *pVtx;		// 頂点情報へのポイント
	int nCntRanking;		// ランキングカウント
	int nCntRankingData;	// ランキングカウント
	int nRanking;			// 桁ランキング
	float fRanking;
	Load *pLoad;

	pLoad = CLoad::GetLoad();

	// 頂点データの範囲をロックし、頂点バッファへのポインタ
	m_pVtxBuffRanking->Lock(0, 0, (void **)&pVtx, 0);


	for (nCntRankingData = 0; nCntRankingData < RANKING_DATE; nCntRankingData++, pLoad++)
	{
		m_aRankin[nCntRankingData].nPoint = pLoad->nPoint;

		for (nCntRanking = 0; nCntRanking < RANKING_MAX; nCntRanking++)
		{
			nRanking = m_aRankin[nCntRankingData].nPoint % (int)powf(10.0f, (float)nCntRanking + 1.0f) / (int)powf(10.0f, (float)nCntRanking);
			fRanking = (float)nRanking / 10.0f;

			pVtx[0].pos = D3DXVECTOR3(m_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				m_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData, 0.0f);							// 一つ目の頂点
			pVtx[1].pos = D3DXVECTOR3(m_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				m_RankingPos.y + (-RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData, 0.0f);							// 二つ目の頂点
			pVtx[2].pos = D3DXVECTOR3(m_RankingPos.x + (-RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking,
				m_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData + RANKING_SIZE, 0.0f);				// 三つ目の頂点
			pVtx[3].pos = D3DXVECTOR3(m_RankingPos.x + (RANKING_SIZE / 2) - (RANKING_SIZE + 20) * nCntRanking + RANKING_SIZE,
				m_RankingPos.y + (RANKING_SIZE / 2) + (RANKING_SIZE + 60) * nCntRankingData + RANKING_SIZE, 0.0f);				// 四つ目の頂点

			pVtx[0].tex = D3DXVECTOR2(fRanking,  0.0f);				// 一つ目のテクスチャ
			pVtx[1].tex = D3DXVECTOR2(fRanking + 0.1f, 0.0f);		// 二つ目のテクスチャ
			pVtx[2].tex = D3DXVECTOR2(fRanking,  1.0f);				// 三つ目のテクスチャ
			pVtx[3].tex = D3DXVECTOR2(fRanking + 0.1f, 1.0f);		// 四つ目のテクスチャ

			pVtx += 4;
		}
	}
	// アンロック
	m_pVtxBuffRanking->Unlock();
}
//=============================================================================
// クリエイト
//=============================================================================
CRanking * CRanking::Create()
{
	CRanking *pRanking;

	pRanking = new CRanking(OBJECT_TYPE_UI);

	pRanking->Init();

	return pRanking;
}
