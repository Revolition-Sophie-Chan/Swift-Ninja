//=============================================================================
//
// スコア処理 [score.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "number.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAXSCORENUM	(3)


class CNumber;
//=============================================================================
//クラス
//=============================================================================
class CScore : public CScene
{
public:

	CScore(OBJECT_TYPE type);
	~CScore();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore *Create(int nScore);
	static int GetScore(void);
	static CNumber *GetaScore();

	void AddScore(int nValue);
	void SetScore(int nScore);
private:

	static CNumber *m_apScore[MAXSCORENUM];
	static int m_nScore;				// スコア
};
#endif
