//=============================================================================
//
// フェード処理 [fade.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_


//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//フェードのクラス
//=============================================================================
class CFade 
{
public:
	// フェードの状態
	enum FADE
	{
		FADE_NONE = 0,		// 何もない状態
		FADE_IN,			// フェードイン処理
		FADE_OUT,			// フェードアウト処理
		FADE_MAX
	} ;
	void InitFade();
	void UninitFade(void);
	void UpdateFade(void);
	void DrawFade(void);
	static void SetFade(CManager::MODE modeNext);
	static FADE GetFade(void);

private:
	LPDIRECT3DTEXTURE9 m_pTextureFade;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade;	// 頂点バッファへのポインタ
	static CManager::MODE m_NextMode;		// 次の画面（モード）
	static FADE m_Fade;
	static D3DXCOLOR m_FadeColor;
};
#endif
