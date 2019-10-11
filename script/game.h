//=============================================================================
//
// ゲーム本編の処理[game.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#define _CRT_SECURE_NO_WARNINGS

//インクルードファイル
#include "main.h"

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
class CGame;
class CTitle;
class CFade;

//=============================================================================
//クラス
//=============================================================================
class CGame
{
public:

	CGame();
	~CGame();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGame *Create(void);
	int nCountTime;
	static CGame *GetGame(void);
	static bool bDamage;
	static bool bPause;
private:
	static CGame *m_pGame;
	bool GetPause(void);
	bool GetDamage(void);
	int nCountGame;
	int nCountDamage;
};

#endif