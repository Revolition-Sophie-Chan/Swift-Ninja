//=============================================================================
//
// 敵の処理[enemy.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//=============================================================================
//インクルード
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//前方宣言
//=============================================================================
class CPlayer;

//=============================================================================
//敵のクラス
//=============================================================================
class CEnemy : public CScene2D
{
public:
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
	static CEnemy *GetEnemy(void);

private:
	void MakeParticle(void);
	void EnemyMove(void);
	void EnemyRelease(void);

	static LPDIRECT3DTEXTURE9 m_apTexturePolygon;//テクスチャへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 PlayerPos;
	int  m_Life;
	int  nCountDamage;
	int  nCountCamera;
	int  nCountEnemyAnim;
	int  nPattenEnemyAnim;
	int  nDirectionEnemyMove;
	bool bJump;
	static CEnemy *m_pEnemy;

};
#endif