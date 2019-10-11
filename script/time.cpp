//=============================================================================
//
// スコア処理 [Time.cpp]
// Author : Tanaka rikiya
//
//=============================================================================
#include "time.h"
#include "renderer.h"
#include "scene2D.h"
//LPDIRECT3DTEXTURE9 CTime::g_pTextureTime[MAXTIMENUM] = {};
int CTime::m_nTime = NULL;
CNumber *CTime::m_apTime[MAXTIMENUM] = {};
//=============================================================================
// マクロ定義
//=============================================================================
#define TIME_POS_X		(430.0f)
#define TIME_POS_Y		(620.0f)
#define TIME_SIZE_X		(20)
#define TIME_SIZE_Y		(30)

//=============================================================================
//コンストラクタ
//=============================================================================
CTime::CTime(OBJECT_TYPE type ) : CScene(type)
{
	
}
//=============================================================================
//デストラクタ
//=============================================================================
CTime::~CTime()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
void CTime::Init(void)
{
	int nTime = CTime::GetTime();
	D3DXVECTOR3 pos;

		for (int nCntTime = 0; nCntTime < MAXTIMENUM; nCntTime++)
		{
			pos = D3DXVECTOR3(TIME_POS_X + (TIME_SIZE_Y + 5.0f)*nCntTime, TIME_POS_Y + TIME_SIZE_Y + 5.0f, 0.0f);
			int nDigits = nTime % (int)powf(10.0f, (float)MAXTIMENUM - nCntTime) / (int)powf(10.0f, (float)MAXTIMENUM - 1.0f - nCntTime);
			m_apTime[nCntTime] = CNumber::Create(pos, TIME_SIZE_X, TIME_SIZE_Y, nDigits);
		}
}

//=============================================================================
// 終了処理
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCntTime = 0; nCntTime < MAXTIMENUM; nCntTime++)
	{
		m_apTime[nCntTime]->Uninit();
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CTime::Update(void)
{
	for (int nCntTime = 0; nCntTime < MAXTIMENUM; nCntTime++)
	{
		m_apTime[nCntTime]->Update();
		if (m_nTime <= 10 )
		{
			m_apTime[nCntTime]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
			m_apTime[nCntTime]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < MAXTIMENUM; nCntTime++)
	{
		m_apTime[nCntTime]->Draw();
	}
}

//=============================================================================
// ポリゴンのクリエイト
//=============================================================================
CTime *CTime::Create(int nTime)
{
	CTime *pTime;

	pTime = new CTime(OBJECT_TYPE_UI);

	pTime->SetTime(nTime);

	pTime->Init();

	return pTime;
}
//=============================================================================
// スコアの変更
//=============================================================================
void CTime::AddTime(int nValue)
{
	m_nTime += nValue;
	if (m_nTime <= 0)
	{
		m_nTime = 0;
	}
	for (int nCntTime = 0; nCntTime < MAXTIMENUM; nCntTime++)
	{
		int nDigits = m_nTime % (int)powf(10.0f, (float)MAXTIMENUM - nCntTime) / (int)powf(10.0f, (float)MAXTIMENUM - nCntTime - 1.0f);
		m_apTime[nCntTime]->SetTex(nDigits);
	}

}
//=============================================================================
// Timeの取得
//=============================================================================
int CTime::GetTime(void)
{
	return m_nTime;
}
//=============================================================================
// Timeの取得
//=============================================================================
CNumber * CTime::GetaTime()
{
	return m_apTime[MAXTIMENUM];
}
//=============================================================================
// スコアのセット
//=============================================================================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;
}

