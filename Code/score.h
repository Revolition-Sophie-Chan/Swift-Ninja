//=============================================================================
//
// �X�R�A���� [score.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "number.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAXSCORENUM (3)

//=============================================================================
//�O���錾
//=============================================================================
class CNumber;

//=============================================================================
//�X�R�A�̃N���X
//=============================================================================
class CScore : public CScene
{
public:

	CScore(OBJECT_TYPE type);
	~CScore();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScore *Create(int nScore);
	static int GetScore(void);
	static CNumber *GetaScore();

	void AddScore(int nValue);
	void SetScore(int nScore);
private:

	static CNumber *m_apScore[MAXSCORENUM];
	static int m_nScore;				// �X�R�A
};
#endif
