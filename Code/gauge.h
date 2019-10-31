//=========================================================================
//
// ゲージ処理 [gauge.h]
// Author : Tanaka Rikiya
//
//=========================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#define DIRECTINPUT_VERSION (0x0800) // 警告対処用

//=========================================================================
//インクルードファイル 
//=========================================================================
#include "main.h"
#include "scene2D.h"

//=========================================================================
//ゲージのクラス
//=========================================================================
class CGauge : public CScene2D
{
public:
	// UIの種類
	typedef enum
	{
		UITYPE_FEVER = 0,
		UITYPE_HP,
		UITYPE_FEVERMAX,
		UITYPE_HPMAX,
		UITYPE_MAX,
	} GAUGETYPE;

	CGauge(OBJECT_TYPE type);
	~CGauge();
	static void Load(void);
	static void Unload(void);
	static CGauge *Create(D3DXVECTOR3 pos,D3DXCOLOR col,float fWight, float fHeight, GAUGETYPE nType);

	void Init(float fWight, float fHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void HPManager(void);

	GAUGETYPE GetGaugeType(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTextureGauge[UITYPE_MAX];	// テクスチャへのポインタ

	int nLife;
	int m_MaxGauge;
	int nFeverCount;
	int nCountTexture;

	GAUGETYPE	m_nType;

	float m_Tex;
	float m_fWigth;
	float m_fHeight;
	float nFeverTime;

protected:

};
#endif

