//=============================================================================
//
// ランキング処理 [ranking.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "Scene.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define RANKING_DATE (5) //ランキング数

//================================================================
//ランキングのクラス
//================================================================
class CRanking : public CScene
{
public:

	//====================================================================================================
	//構造体定義
	//=====================================================================================================
	typedef struct
	{
		D3DXVECTOR3 pos;	//ポジション
		float       rhw;	//1で固定する
		D3DCOLOR    col;	//色
		D3DXVECTOR2 tex;	//テクスチャ情報
	}VERTEX_2D;

	typedef struct
	{
		D3DXVECTOR3 pos;
		char aName[128];
		int nPoint;
	} RANKING;

	CRanking(OBJECT_TYPE type);
	~CRanking();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ランキング計算関数
	void AddRanking(int nPoint, int nRanking);
	static CRanking * Create();

private:
	void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

	LPDIRECT3DTEXTURE9		m_pTextureRanking;				// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffRanking;				// 頂点バッファへのポインタ
	D3DXVECTOR3				m_RankingPos;							// ランキングボードのポジション
	RANKING					m_aRankin[RANKING_DATE];				// ランキング変数
	
	int m_nRanking;
	int m_nRNKData;
};
#endif
