//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "score.h"
#include "renderer.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
int CScore::m_nScore = NULL;
CNumber *CScore::m_apScore[MAXSCORENUM] = {};

//=============================================================================
// �}�N����`
//=============================================================================
#define SCORE_POS_X			(1100.0f)
#define SCORE_POS_Y			(630.0f)
#define SCORE_SIZE_X		(20)
#define SCORE_SIZE_Y		(40)
#define RANKSCORE_POS_X		(900.0f)
#define RANKSCORE_POS_Y		(400.0f)
#define RANKSCORE_SIZE_X	(40)
#define RANKSCORE_SIZE_Y	(80)

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScore::CScore(OBJECT_TYPE type ) : CScene(type)
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
// ��������
//=============================================================================
CScore *CScore::Create(int nScore)
{
	CScore *pScore;
	pScore = new CScore(OBJECT_TYPE_UI);
	pScore->SetScore(nScore);
	pScore->Init();
	return pScore;
}

//=============================================================================
// ����������
//=============================================================================
void CScore::Init(void)
{	int nScore = CScore::GetScore();
	D3DXVECTOR3 pos;
	if (CManager::GetMode() == CManager::MODE_GAME|| CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
		{
			pos = D3DXVECTOR3(SCORE_POS_X + (SCORE_SIZE_Y)*nCntScore, SCORE_POS_Y + SCORE_SIZE_Y, 0.0f);
			int nDigits = nScore % (int)powf(10.0f, (float)MAXSCORENUM - nCntScore) / (int)powf(10.0f, (float)MAXSCORENUM - 1.0f - nCntScore);
			m_apScore[nCntScore] = CNumber::Create(pos, SCORE_SIZE_X, SCORE_SIZE_Y, nDigits);
		}
	}
	if (CManager::GetMode() == CManager::MODE_RANKING)
	{
		for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
		{
			pos = D3DXVECTOR3(RANKSCORE_POS_X + (RANKSCORE_SIZE_Y)*nCntScore, RANKSCORE_POS_Y + RANKSCORE_SIZE_Y, 0.0f);
			int nDigits = nScore % (int)powf(10.0f, (float)MAXSCORENUM - nCntScore) / (int)powf(10.0f, (float)MAXSCORENUM - 1.0f - nCntScore);
			m_apScore[nCntScore] = CNumber::Create(pos, RANKSCORE_SIZE_X, RANKSCORE_SIZE_Y, nDigits);
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		m_apScore[nCntScore]->Uninit();
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CScore::Update(void)
{
	for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		m_apScore[nCntScore]->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		m_apScore[nCntScore]->Draw();
	}
}

//=============================================================================
// �X�R�A�̕ύX
//=============================================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
	if (m_nScore <= 0)
	{
		m_nScore = 0;
	}
	for (int nCntScore = 0; nCntScore < MAXSCORENUM; nCntScore++)
	{
		int nDigits = m_nScore % (int)powf(10.0f, (float)MAXSCORENUM - nCntScore) / (int)powf(10.0f, (float)MAXSCORENUM - nCntScore - 1.0f);
		m_apScore[nCntScore]->SetTex(nDigits);
	}
}

//=============================================================================
// score�̎擾
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//=============================================================================
// score�̎擾
//=============================================================================
CNumber * CScore::GetaScore()
{
	return m_apScore[MAXSCORENUM];
}

//=============================================================================
// �X�R�A�̃Z�b�g
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

