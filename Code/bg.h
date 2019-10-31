//=============================================================================
//
// 背景の処理[bg.h]
// Author : Tanaka Rikiya
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
//背景のクラス
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
	static LPDIRECT3DTEXTURE9 m_pTextureBg;//テクスチャへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
};
#endif