
//=============================================================================
//
// 敵の処理[enemy.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"manager.h"
#include "scene.h"

#include "scene2D.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_ENEMY_TEXTURE (2)

//=============================================================================
//クラス
//=============================================================================
class CPlayer;
class CEnemy : public CScene2D
{
public:
	typedef enum
	{//状態
		ENEMYSTATE_NORMAL = 0,
		ENEMYSTATE_UNDYING,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_DEATH,
		ENEMYSTATE_MAX,
	} ENEMYSTATE;

	CEnemy(OBJECT_TYPE type);
	 ~CEnemy();
	 void Init(void);
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	static CEnemy *Create(D3DXVECTOR3 Epos, D3DXVECTOR3 Emove, int Elife);
	void HitEnemy(int Damage);
	D3DXVECTOR3 GetEnemyPos(void);
	ENEMYSTATE GetEnemyState(void);
	static CEnemy *GetEnemy(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexturePolygon;//テクスチャへのポインタ
	//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 PlayerPos;
	int m_nCountRot = 0;
	bool bJump = false; 
	int nDirectionEnemyMove = 0;
	int m_Life;
	int nPattenEnemyAnim;
	int nCountEnemyAnim;
	int nCountDamage;
	int nCountCamera;
	void MakeParticle(void);
	static CEnemy *m_pEnemy;
	ENEMYSTATE EnemyState;
};
#endif