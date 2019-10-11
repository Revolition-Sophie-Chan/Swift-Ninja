//=========================================================================
//
// ゲージ処理 [gauge.h]
// Author : tanaka rikiya
//
//=========================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#define DIRECTINPUT_VERSION (0x0800) // 警告対処用

//=========================================================================
// インクルードファイル 
//=========================================================================
#include "main.h"
#include "Scene2D.h"

//=========================================================================
// 前方宣言
//=========================================================================

//=========================================================================
// マクロ定義 
//========================================================================= 
#define GAUGE_SIZE			(15.0f)		// 大きさ
	
//=========================================================================
// UIクラス(継承)
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
	int nFeverCount;
	int nLife;
	int nCountTexture;
	float nFeverTime;
	float m_Tex;
	int m_MaxGauge;

	GAUGETYPE	m_nType;	// 種類
	float		m_fWigth;	// 幅
	float		m_fHeight;	// 高さ

protected:

};
#endif

