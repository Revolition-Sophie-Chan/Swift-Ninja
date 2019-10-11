//=============================================================================
//
// ランキング処理 [rankingall.h]
// Author :  tanakarikiya
//
//=============================================================================
#ifndef _RANKINGALL_H_
#define _RANKINGALL_H_

//=============================================================================
//
// インクルードファイル
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include "Scene.h"

#define RANKING_DATE (5)									// ランキング数

class CRanking;
//================================================================
// レンダリングクラス
//================================================================
class CRankingAll
{
public:

	CRankingAll();
	~CRankingAll();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ランキング計算関数
	static CRankingAll * Create();

private:
	int FadeCount;
	static CRanking *pRanking;
};
#endif

