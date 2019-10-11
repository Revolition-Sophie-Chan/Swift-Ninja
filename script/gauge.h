//=========================================================================
//
// �Q�[�W���� [gauge.h]
// Author : tanaka rikiya
//
//=========================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#define DIRECTINPUT_VERSION (0x0800) // �x���Ώ��p

//=========================================================================
// �C���N���[�h�t�@�C�� 
//=========================================================================
#include "main.h"
#include "Scene2D.h"

//=========================================================================
// �O���錾
//=========================================================================

//=========================================================================
// �}�N����` 
//========================================================================= 
#define GAUGE_SIZE			(15.0f)		// �傫��
	
//=========================================================================
// UI�N���X(�p��)
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
	int nFeverCount;
	int nLife;
	int nCountTexture;
	float nFeverTime;
	float m_Tex;
	int m_MaxGauge;

	GAUGETYPE	m_nType;	// ���
	float		m_fWigth;	// ��
	float		m_fHeight;	// ����

protected:

};
#endif

