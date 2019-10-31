//=========================================================================
//
// �Q�[�W���� [gauge.h]
// Author : Tanaka Rikiya
//
//=========================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#define DIRECTINPUT_VERSION (0x0800) // �x���Ώ��p

//=========================================================================
//�C���N���[�h�t�@�C�� 
//=========================================================================
#include "main.h"
#include "scene2D.h"

//=========================================================================
//�Q�[�W�̃N���X
//=========================================================================
class CGauge : public CScene2D
{
public:
	// UI�̎��
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
	static LPDIRECT3DTEXTURE9	m_pTextureGauge[UITYPE_MAX];	// �e�N�X�`���ւ̃|�C���^

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

