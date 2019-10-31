//=============================================================================
//
// ゲーム本編の処理[game.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
//インクルード
//=============================================================================
#include "main.h"

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
class CGame;
class CTitle;
class CFade;

//=============================================================================
//ゲーム本編のクラス
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
	static CGame *GetGame(void);

	int nCountTime;

private:
	void CameraShake(void);
	void EnemySpawn(void);
	void LoadAll(void);

	static CGame *m_pGame;
	int nCountGame;
	int nCountDamage;
	int nCountCamera;
};

#endif