//=============================================================================
//
// �����L���O���� [rankingall.h]
// Author :  tanakarikiya
//
//=============================================================================
#ifndef _RANKINGALL_H_
#define _RANKINGALL_H_

//=============================================================================
//
// �C���N���[�h�t�@�C��
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "main.h"
#include "Scene.h"

#define RANKING_DATE (5)									// �����L���O��

class CRanking;
//================================================================
// �����_�����O�N���X
//================================================================
class CRankingAll
{
public:

	CRankingAll();
	~CRankingAll();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �����L���O�v�Z�֐�
	static CRankingAll * Create();

private:
	int FadeCount;
	static CRanking *pRanking;
};
#endif
