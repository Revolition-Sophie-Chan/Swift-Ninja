
//=============================================================================
//
// 管理処理[manager.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include"main.h"

//=============================================================================
// 前方宣言
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

//=============================================================================
//クラス
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
		MODE_RANKING,
		MODE_MAX
	};
	static MODE m_Mode;
	static void SetMode(MODE mode);
	static MODE GetMode(void);
private:

	static CRenderer *m_pRenderer;
	//static CPointer *m_pPointer;
	static CInputkeyborad *m_pKeyborad;
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CGamepad *m_pGamepad;
	static CRankingAll *m_pRanking;
	static CTutorial *m_pTutorial;
	static CSound *m_pSound;
};
#endif
