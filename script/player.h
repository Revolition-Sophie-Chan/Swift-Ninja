
//=============================================================================
//
// プレイヤー処理[player.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// インクルード
//=============================================================================
#include"manager.h"
#include "scene.h"
#include "scene2D.h"
#include "enemy.h"


class CLoad;
class CSave;
//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_PLAYER (20)

//=============================================================================
//クラス
//=============================================================================
class CPlayer : public CScene2D
{
public:
	typedef enum
	{//状態
		PLAYERSTATE_NORMAL = 0,
		PLAYERSTATE_UNDYING,
		PLAYERSTATE_DAMAGE,
		PLAYERSTATE_JUMPUP,
		PLAYERSTATE_DEATH,
		PLAYERSTATE_ATK,
		PLAYERSTATE_COOLDOWN,
		PLAYERSTATE_FINISH,
		PLAYERSTATE_MAX,
	} PLAYERSTATE;

	typedef enum
	{//行動
		PLAYERMOVESTATE_WAIT = 0,
		PLAYERMOVESTATE_MOVE,
		PLAYERMOVESTATE_ATTACK,
		PLAYERMOVESTATE_JUMPUP,
		PLAYERMOVESTATE_JUMPDOWN,
		PLAYERMOVESTATE_DOUBLEJUMP,
		PLAYERMOVESTATE_DAMAGE,
		PLAYERMOVESTATE_DEATH,
		PLAYERMOVESTATE_MAX,
	} PLAYERMOVESTATE;

	CPlayer(OBJECT_TYPE type);
	 ~CPlayer();
	 void Init(void);
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	static CPlayer *Create(D3DXVECTOR3 Playerpos,int nLife);
	static CPlayer *GetPlayer(void);
	D3DXVECTOR3 GetPlayerPos(void);
	void SetAttackRot(float AttackRot);
	bool GetPlayerAttackFlag(void);
	void HitPlayer(int nDamege);
	static int State;
	static int MState;
	static int AnimCount;
	static int nScore;
	static int nFever;
	static bool bShake;
	static bool bFever;
	static bool bRankScore;
	static bool bRoof;
	static bool bFinish;
	static PLAYERSTATE PlayerState;
private:
	bool CollisionPlayer(D3DXVECTOR3 pos);
	static LPDIRECT3DTEXTURE9 m_apTexturePolygon[MAX_PLAYER];//テクスチャへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 PlayerPos;
	int m_nCountRot;
	int nDirectionMove;
	int nCountAttack;
	int nCountCoolDown;
	int nCounterState;
	int nCountDamage;
	int nPattenAnim;
	int nCountAnim;
	int nCountFade;
	int nCountCoolTime;
	int nCountCamera;
	int nCountFever;
	int nLife;
	int m_Color0;

	float m_randColor0;
	int m_Color1;
	float m_randColor1;
	int m_Color2;
	float m_randColor2;


	bool bJump;
	bool bDoubleJump;
	bool bDoubleJumpAnim;
	bool bAttack;
	float m_AttackRot;
	float m_fposSize = 100.0f;

	PLAYERMOVESTATE MoveState;
	static CPlayer *m_pPlayer;
	static CSave *m_Save;
	static CLoad *m_Load;


};
#endif