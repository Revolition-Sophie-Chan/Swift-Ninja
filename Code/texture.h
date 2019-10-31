//=============================================================================
//
// 画像表示の処理[texture.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//=============================================================================
//インクルード
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//画像描画のクラス
//=============================================================================
class CTexture : public CScene2D 
{
public:
	typedef enum
	{
		TYPE_BG,
		TYPE_LOGO,
		TYPE_ENTER,
		TYPE_START,
		TYPE_RANKING,
		TYPE_1ST,
		TYPE_2ND,
		TYPE_3RD,
		TYPE_4TH,
		TYPE_5TH,
		TYPE_RANKCOUNT,
		TYPE_BREAK,
		TYPE_KO,
		TYPE_HP,
		TYPE_TIME,
		TYPE_FEVER,
		TYPE_IN_FEVER01,
		TYPE_IN_FEVER02,
		TYPE_10PLUS,
		TYPE_PAUSECONTINUE,
		TYPE_PAUSERETRY,
		TYPE_PAUSEQUIT,
		TYPE_FINISH,
		TYPE_TUTORIAL00,
		TYPE_TUTORIAL01,
		TYPE_TUTORIAL02,
		TYPE_MAX
	}TEXTURE_TYPE;

	CTexture(OBJECT_TYPE type);
	 ~CTexture();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CTexture *Create(D3DXVECTOR3 TEXpos,float Height,float Weight, TEXTURE_TYPE Texture);
	 TEXTURE_TYPE GetTextureType(void);
	 static bool bINFever;

private:
	void TypeManager(void);

	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];//テクスチャへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	TEXTURE_TYPE TextureType;
	int Count10Time;
	int nCountTexture;
	float TimeColor;

};
#endif