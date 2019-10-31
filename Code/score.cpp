//=============================================================================
//
// スコア処理 [score.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "score.h"
#include "renderer.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
int CScore::m_nScore = NULL;
CNumber *CScore::m_apScore[MAXSCORENUM] = {};

//=============================================================================
// マクロ定義
//=============================================================================
#define SCORE_POS_X			(1100.0f)
#define SCORE_POS_Y			(630.0f)
#define SCORE_SIZE_X		(20)
#define SCORE_SIZE_Y		(40)
#define RANKSCORE_POS_X		(900.0f)
#define RANKSCORE_POS_Y		(400.0f)
#define RANKSCORE_SIZE_X	(40)
#define RANKSCORE_SIZE_Y	(80)

//=============================================================================
//コンストラクタ
//=============================================================================
CScore::CScore(OBJECT_TYPE type ) : CScene(type)
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CScore *CScore::Create(int nScore)
{
	CScore *pScore;
	pScore = new CScore(OBJECT_TYPE_UI);
	pScore->SetScore(nScore);
	pScore->Init();
	return pScore;
}

//=============================================================================
// 初期化処理
//=============================================================================
void CScore::Init(void)
{	int nScore = CScore::GetScore();
	D3DXVECTOR3 pos;
	if (CManager::GetMode() == CManager::MODE_GAME|| CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
		{
			pos = D3DXVECTOR3(SCORE_POS_X + (SCORE_SIZE_Y)*nCntScore, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			int nDigits = nScore % (int)powf(10.0f, (float)MAXSCORENUM - nCntScore) / (int)powf(10.0f, (float)MAXSCORENUM - 1.0f - nCntScore);
			m_apScore[nCntScore] = CNumber::Create(pos, SCORE_SIZE_X, SCORE_SIZE_Y, nDigits);
		}
	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{
		for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
		{
			pos = D3DXVECTOR3(RANKSCORE_POS_X + (RANKSCORE_SIZE_Y)*nCntScore, RANKSCORE_POS_Y + RANKSCORE_SIZE_Y, 0.0f);
			int nDigits = nScore % (int)powf(10.0f, (float)MAXSCORENUM - nCntScore) / (int)powf(10.0f, (float)MAXSCORENUM - 1.0f - nCntScore);
			m_apScore[nCntScore] = CNumber::Create(pos, RANKSCORE_SIZE_X, RANKSCORE_SIZE_Y, nDigits);
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		m_apScore[nCntScore]->Uninit();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CScore::Update(void)
{
	for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		m_apScore[nCntScore]->Update();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		m_apScore[nCntScore]->Draw();
	}
}

//=============================================================================
// スコアの変更
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
	if (m_nScore <= 0)
	{
		m_nScore = 0;
	}
	for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		int nDigits = m_nScore % (int)powf(10.0f, (float)MAXSCORENUM - nCntScore) / (int)powf(10.0f, (float)MAXSCORENUM - nCntScore - 1.0f);
		m_apScore[nCntScore]->SetTex(nDigits);
	}
}

//=============================================================================
// scoreの取得
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//=============================================================================
// scoreの取得
//=============================================================================
CNumber * CScore::GetaScore()
{
	return m_apScore[MAXSCORENUM];
}

//=============================================================================
// スコアのセット
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

