
//=============================================================================
//
// エフェクトの処理[Particle.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//=============================================================================
// インクルード
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define HITSIZE_X (200)
#define HITSIZE_Y (200)

//=============================================================================
//クラス
//=============================================================================
class CParticle : public CScene2D 
{
public:
	CParticle(OBJECT_TYPE type);
	 ~CParticle();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CParticle *Create(D3DXVECTOR3 ParticlePos,D3DXVECTOR3 ParticleMove , D3DXCOLOR Particlecol, float fRadius);
	 D3DXCOLOR GetParticleColer(void);
private:
	int m_nLife;
	//VERTEX_2D m_aVertex[4];
	static LPDIRECT3DTEXTURE9 m_pTextureParticle[MAX_TEXTURE];//テクスチャへのポインタ
	//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;//頂点バッファへのポインタ
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	int m_nCountRot = 0;
	float m_fposSize = 100.0f;
	float m_fRadius=0.0f;
};
#endif