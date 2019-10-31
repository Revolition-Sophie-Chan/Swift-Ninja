//=============================================================================
//
// エフェクトの処理[effect.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
//インクルード
//=============================================================================

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_EFFECT (3)

//=============================================================================
//エフェクトクラス
//=============================================================================
class CEffect : public CScene2D 
{
public:
	CEffect(OBJECT_TYPE type);
	~CEffect();
	void Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CEffect *Create(D3DXVECTOR3 Effectpos, D3DXCOLOR Effectcol, D3DXVECTOR3 Effectmove,float Size,int Effect_Number,int EffectLife);

private:
	D3DXVECTOR3 size;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTextureEffect[MAX_EFFECT];//テクスチャへのポインタ
};
#endif