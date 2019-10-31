//=============================================================================
//
// 管理処理[manager.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//=============================================================================
// インクルード
//=============================================================================
#include"main.h"

//=============================================================================
//前方宣言
//=============================================================================
class CRender;
class CInputkeyborad;
class CBg;
class CPlayer;
class CEnemy;
class CBullet;
class CExplosion;
class CNumber;
class CPointer;
class CHere;
class CTitle;
class CGame;
class CJoypad;
class CGamepad;
class CRankingAll;
class CSound;
class CTutorial;
class CPause;

//=============================================================================
//管理のクラス
//=============================================================================
class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hinstance,HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	static CRenderer *GetRenderer(void);
	static CInputkeyborad *GetInputKeyboard(void);
	static CInputkeyborad *m_pInputKeyboard(void);
	static CGamepad *GetGamePad(void);
	static CRankingAll *GetRanking(void);
	static CTutorial *GetTutorial(void);
	static CSound *GetSound(void);

	enum MODE
	{
		MODE_TITLE = 0,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_PAUSE,
		MODE_RANKING,
		MODE_MAX
	};
	static MODE m_Mode;
	static void SetMode(MODE mode);
	static CManager::MODE SetPause(CManager::MODE mode);
	static MODE GetMode(void);

private:
	static CGame *m_pGame;
	static CTitle *m_pTitle;
	static CPause *m_pPause;
	static CSound *m_pSound;
	static CGamepad *m_pGamepad;
	static CRenderer *m_pRenderer;
	static CTutorial *m_pTutorial;
	static CRankingAll *m_pRanking;
	static CInputkeyborad *m_pKeyborad;
};
#endif
