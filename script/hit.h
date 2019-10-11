
//=============================================================================
//
// 爆発の処理[hit.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _HIT_H_
#define _HIT_H_

#include "manager.h"
#include "scene.h"

#include "scene2D.h"


//=============================================================================
//マクロ定義
//=============================================================================
#define HIT_ANIM (5)
#define MAX_HIT (4)
//=============================================================================
//クラス
//=============================================================================
class CHit : public CScene2D
{
public:
	CHit(OBJECT_TYPE type);
	 ~CHit();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CHit *Create(D3DXCOLOR Hitcol,int type, int nLife);
private:

	int m_nLife;
	//VERTEX_2D m_aVertex[4];
	static LPDIRECT3DTEXTURE9 m_pTexturehit[MAX_HIT];//テクスチャへのポインタ
	//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
};
#endif