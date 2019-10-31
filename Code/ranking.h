//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "Scene.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define RANKING_DATE (5) //�����L���O��

//================================================================
//�����L���O�̃N���X
//================================================================
class CRanking : public CScene
{
public:

	//====================================================================================================
	//�\���̒�`
	//=====================================================================================================
	typedef struct
	{
		D3DXVECTOR3 pos;	//�|�W�V����
		float       rhw;	//1�ŌŒ肷��
		D3DCOLOR    col;	//�F
		D3DXVECTOR2 tex;	//�e�N�X�`�����
	}VERTEX_2D;

	typedef struct
	{
		D3DXVECTOR3 pos;
		char aName[128];
		int nPoint;
	} RANKING;

	CRanking(OBJECT_TYPE type);
	~CRanking();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �����L���O�v�Z�֐�
	void AddRanking(int nPoint, int nRanking);
	static CRanking * Create();

private:
	void MakeVertexRanking(LPDIRECT3DDEVICE9 pDevice);

	LPDIRECT3DTEXTURE9		m_pTextureRanking;				// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffRanking;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_RankingPos;							// �����L���O�{�[�h�̃|�W�V����
	RANKING					m_aRankin[RANKING_DATE];				// �����L���O�ϐ�
	
	int m_nRanking;
	int m_nRNKData;
};
#endif
