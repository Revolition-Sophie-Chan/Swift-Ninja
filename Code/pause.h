//=============================================================================
//
// ポーズ画面の処理[pause.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"
#include "manager.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define PAUSESELECT (3)

//=============================================================================
//前方宣言
//=============================================================================
class CTexture;

//=============================================================================
//ポーズのクラス
//=============================================================================
class CPause
{
public:
	enum PAUSE_STATE
	{
		PAUSESTATE_CONTINUE,
		PAUSESTATE_RETRY,
		PAUSESTATE_QUIT,
		PAUSESTATE_MAX
	};

	CPause();
	~CPause();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetDraw(bool bDraw);
	static CPause *Create();

	static PAUSE_STATE GetPauseState(); 
	static void SetPauseState(PAUSE_STATE state);


private:
	void SetSelectSize(int Size);

	CTexture *m_pPauseTexture[PAUSESELECT];


	static PAUSE_STATE PauseState;
	int		StateCount;
	float	Size_X;
	float	Size_Y;
	bool	bSelect;
	bool	bSize;
};
#endif