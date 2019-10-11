//=============================================================================
//
// セーブ処理 [save.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "save.h"
#include "load.h"
#include "renderer.h"

CSave::SAVE	CSave::m_aSave[MAX_LOAD] = {};

//=============================================================================
// マクロ定義
//=============================================================================
#define	TEXTURE_SAVE		"Data/Texture/number002.png"	// 読み込むテキストファイル名
#define SAVE_SIZE (20)										// セーブボードの大きさ
#define SAVE_MAX (10)										// 数値
#define SAVE_DATE (5)										// セーブの個数
#define SAVE_FILE_NAME ("Data/text.txt")					// セーブファイル

//=============================================================================
// 初期化処理
//=============================================================================
void CSave::InitSave(void)
{
	int nCntSave;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++)
	{
		m_aSave[nCntSave].aName[nCntSave];
		m_aSave[nCntSave].nPoint = 0;
	}
}

//=============================================================================
// セーブ関数
//=============================================================================
void CSave::SaveData(int nPoint)
{
	// ファイルポイント
	FILE *pFile;
	int aDate[6] = {};
	int nDate;
	int nCntSave;
	int nCntNum;

	Load *pLoad;

	pLoad = CLoad::GetLoad();

	for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++, pLoad++)
	{
		m_aSave[nCntSave].nPoint = pLoad->nPoint;
		aDate[nCntSave] = m_aSave[nCntSave].nPoint;
	}
	aDate[5] = nPoint;

	for (nCntSave = 0; nCntSave < SAVE_DATE + 1; nCntSave++)
	{
		for (nCntNum = nCntSave + 1; nCntNum < SAVE_DATE + 1; nCntNum++)
		{
			if (aDate[nCntSave] < aDate[nCntNum])
			{
				nDate = aDate[nCntNum];
				aDate[nCntNum] = aDate[nCntSave];
				aDate[nCntSave] = nDate;
			}
		}
	}

	// ファイル
	pFile = fopen(SAVE_FILE_NAME, "w");

	// 開けた
	if (pFile != NULL)
	{
		for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++)
		{
			fprintf(pFile, "%d\n\n", aDate[nCntSave]);	// ポイント
		}
		// ファイル閉
		fclose(pFile);
	}
	// 開けない
	else
	{
		printf("開けませんでした\n");
	}
}

//=============================================================================
// セーブデータ取得
//=============================================================================
CSave::SAVE *CSave::GetSave(void)
{
	return &m_aSave[0];
}

//=============================================================================
// クリエイト
//=============================================================================
CSave * CSave::Create()
{
	CSave *pSave;

	pSave = new CSave();

	pSave->InitSave();

	return pSave;
}

//=============================================================================
// コンストラクト
//=============================================================================
CSave::CSave()
{
}

//=============================================================================
// デストラクト
//=============================================================================
CSave::~CSave()
{
}
