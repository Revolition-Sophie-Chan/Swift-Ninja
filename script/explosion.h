
//=============================================================================
//
// 爆発の処理[explosion.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "manager.h"
#include "scene.h"

#include "scene2D.h"

//=============================================================================
//クラス
//=============================================================================
class CExplosion : public CScene2D
{
public:
	typedef enum
	{
		EXPLOSIONTYPE_ENEMY = 0,
		EXPLOSIONTYPE_JUMP,
		EXPLOSIONTYPE_TIME,
		EXPLOSIONTYPE_MAX,
	} EXPLOSIONTYPE;

	CExplosion(OBJECT_TYPE type);
	 ~CExplosion();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CExplosion *Create(D3DXVECTOR3 EPpos,int nLife,int nCount,EXPLOSIONTYPE nType);
	 EXPLOSIONTYPE GetType();
private:

	int m_nLife;
	//VERTEX_2D m_aVertex[4];
	static LPDIRECT3DTEXTURE9 m_pTextureExplosion[EXPLOSIONTYPE_MAX];//テクスチャへのポインタ
	//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	int m_nCountRot = 0;
	int nPattenExplosionAnim;
	int nCountExplosionAnim;
	float m_fRot = D3DX_PI*0.25f;
	float m_fposSize = 100.0f;
	EXPLOSIONTYPE ExplosionType;
};
#endif