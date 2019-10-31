//=============================================================================
//
// アイコンの処理[icon.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _ICON_H_
#define _ICON_H_

//=============================================================================
//インクルード
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//アイコンのクラス
//=============================================================================
class CIcon : public CScene2D 
{
public:
	CIcon(OBJECT_TYPE type);
	 ~CIcon();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CIcon *Create(D3DXVECTOR3 Iconpos);

private:
	static LPDIRECT3DTEXTURE9 m_pTextureIcon;//テクスチャへのポインタ
	bool bFlag;
};
#endif