//=============================================================================
//
// タイトルの処理[Pause.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#define _CRT_SECURE_NO_WARNINGS

//インクルードファイル
#include "main.h"
#include "manager.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define PAUSESELECT (3)

class CTexture;
//=============================================================================
//クラス
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
	bool bSelect;
	CTexture *m_pPauseTexture[PAUSESELECT];
	int StateCount;
	static PAUSE_STATE PauseState;


};
#endif