//=============================================================================
//
// ナンバー処理[Number.h]
// Author：tanaka rikiya
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_
#define DIRECTINPUT_VERSION (0x0800)

//=============================================================================
// インクルード
//=============================================================================
#include"main.h"

//=============================================================================
//クラス
//=============================================================================
class CNumber
{
public:

	typedef enum
	{
		TYPE_NORMAL,
		TYPE_HP
	}TYPE_NUMBER;

	CNumber();
	~CNumber();

	HRESULT Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);

	static HRESULT Load(void);
	static void Unload(void);
	static CNumber *Create(D3DXVECTOR3 pos,float size_x,float size_y,int nNumber);
	void SetNumber(int nNumber);
	void SetPosition(D3DXVECTOR3 pos);
	void SetSize(float size_x, float size_y);
	void SetTex(int nDigits);
	void SetHeart(int Heart);
	void SetColor(D3DXCOLOR col);
private:
	TYPE_NUMBER NumType;
	static LPDIRECT3DTEXTURE9 m_pTextureNumber; 
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffNumber;
	D3DXVECTOR3 m_pos;
	D3DXCOLOR m_col;
	float m_size_X;
	float m_size_Y;
	int m_nNumber;
};
#endif