
//=============================================================================
//
// 背景の処理[Bg.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//=============================================================================
//インクルード
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//マクロ定義
//=============================================================================
//=============================================================================
//クラス
//=============================================================================
class CBg : public CScene2D 
{
public:
	CBg(OBJECT_TYPE type);
	 ~CBg();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CBg *Create(D3DXVECTOR3 BGpos);
private:

	int m_nLife;
	//VERTEX_2D m_aVertex[4];
	static LPDIRECT3DTEXTURE9 m_pTextureBg;//テクスチャへのポインタ
	//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	int m_nCountRot = 0;
};
#endif