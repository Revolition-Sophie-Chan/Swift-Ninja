//=============================================================================
//
// ロード処理 [load.cpp]
// Author : tanaka rikiya
//
//=============================================================================

//=============================================================================
//インクルード
//=============================================================================
#include "load.h"
#include <stdio.h>
#include "enemy.h"
#include "save.h"

//=============================================================================
//静的メンバ変数の初期化
//=============================================================================
Load CLoad::m_aLoad[MAX_ENEMYLOAD] = {};

//============================================================================
//マクロ定義
//============================================================================
#define	TEXTURE_LOAD		"Data/Texture/number002.png"	// 読み込むテクスチャファイル名
#define LOAD_SIZE (20)								// ロードボードの大きさ
#define LOAD_MAX (10)								// 数値
#define LOAD_DATE (5)								// ロード数
#define SAVE_FILE_NAME ("Data/text.txt") // セーブファイル

//=============================================================================
//コンストラクタ
//=============================================================================
CLoad::CLoad()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CLoad::~CLoad()
{
}

//=============================================================================
//
//初期化処理
//
//=============================================================================
void CLoad::InitLoad(void)
{
	int nCntLoad;

	for (nCntLoad = 0; nCntLoad < MAX_ENEMYLOAD; nCntLoad++)
	{
		m_aLoad[nCntLoad].aName[nCntLoad];
		m_aLoad[nCntLoad].nPoint = 0;
	}

	LoadData();
}

//=============================================================================
//データ取得
//=============================================================================
Load *CLoad::GetLoad(void)
{
	return &m_aLoad[0];
}

//=============================================================================
//メモリの確保
//=============================================================================
CLoad * CLoad::Create()
{
	CLoad *pLoad;

	pLoad = new CLoad();

	pLoad->InitLoad();

	return pLoad;
}

//=============================================================================
//ロード関数
//=============================================================================
void CLoad::LoadData(void)
{
	// ファイルポイント
	FILE *pFile;

	int nCntLoad;

	// ファイル開
	pFile = fopen(SAVE_FILE_NAME, "r");

	// 開けた
	if (pFile != NULL)
	{
		for (nCntLoad = 0; nCntLoad < MAX_ENEMYLOAD; nCntLoad++)
		{
			fscanf(pFile, "%d", &m_aLoad[nCntLoad].nPoint); // 名前
		}
		// ファイル
		fclose(pFile);
	}

	// 開けない
	else
	{
		printf("開けませんでした\n");
	}
}

//=============================================================================
//ロード関数
//=============================================================================
void CLoad::LoadObject(void)
{
}