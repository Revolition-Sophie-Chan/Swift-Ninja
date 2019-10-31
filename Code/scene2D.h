//=============================================================================
//
// ポリゴン処理[scene2D.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
#define DIRECTINPUT_VERSION (0x0800)

//=============================================================================
//インクルード
//=============================================================================
#include "manager.h"
#include "scene.h"

//=============================================================================
//2Dテクスチャのクラス
//=============================================================================
class CScene2D : public CScene
{
public:
	CScene2D(OBJECT_TYPE type);
	 ~CScene2D();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindTexture(LPDIRECT3DTEXTURE9 m_pSetTexture);

	void SetAnim(int, int, int);
	void SetPosition(D3DXVECTOR3 pos);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(float m_rot);
	void SetColor(D3DXCOLOR col);
	void SetSize(float fSize_X,float fSize_Y);
	void SetRadius(float Radius);
	void SetLife(int nLife);
	void SetGauge(float nWight,float nHeight);

	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	float GetRot(void);
	D3DXCOLOR GetColor(void);
	D3DXVECTOR3 GetSize(void);
	int GetLife(void);

	void InitTex(int Height, float Weight);
	void TextureMove(void);

	bool m_bDraw;

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_size;
	D3DXCOLOR m_col;
	LPDIRECT3DTEXTURE9 m_pTexture;//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;//頂点バッファへのポインタ

	int m_CountAnim;
	int nPattenAnim;
	int m_Life;
	float m_fRot;
	float m_Size_X;
	float m_Size_Y;
	float m_Movetex;
	float m_Radius;
};
#endif