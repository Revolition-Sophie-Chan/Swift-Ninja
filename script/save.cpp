//=============================================================================
//
// �Z�[�u���� [save.cpp]
// Author : tanaka rikiya
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "save.h"
#include "load.h"
#include "renderer.h"

CSave::SAVE	CSave::m_aSave[MAX_LOAD] = {};

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_SAVE		"Data/Texture/number002.png"	// �ǂݍ��ރe�L�X�g�t�@�C����
#define SAVE_SIZE (20)										// �Z�[�u�{�[�h�̑傫��
#define SAVE_MAX (10)										// ���l
#define SAVE_DATE (5)										// �Z�[�u�̌�
#define SAVE_FILE_NAME ("Data/text.txt")					// �Z�[�u�t�@�C��

//=============================================================================
// ����������
//=============================================================================
void CSave::InitSave(void)
{
	int nCntSave;
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++)
	{
		m_aSave[nCntSave].aName[nCntSave];
		m_aSave[nCntSave].nPoint = 0;
	}
}

//=============================================================================
// �Z�[�u�֐�
//=============================================================================
void CSave::SaveData(int nPoint)
{
	// �t�@�C���|�C���g
	FILE *pFile;
	int aDate[6] = {};
	int nDate;
	int nCntSave;
	int nCntNum;

	Load *pLoad;

	pLoad = CLoad::GetLoad();

	for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++, pLoad++)
	{
		m_aSave[nCntSave].nPoint = pLoad->nPoint;
		aDate[nCntSave] = m_aSave[nCntSave].nPoint;
	}
	aDate[5] = nPoint;

	for (nCntSave = 0; nCntSave < SAVE_DATE + 1; nCntSave++)
	{
		for (nCntNum = nCntSave + 1; nCntNum < SAVE_DATE + 1; nCntNum++)
		{
			if (aDate[nCntSave] < aDate[nCntNum])
			{
				nDate = aDate[nCntNum];
				aDate[nCntNum] = aDate[nCntSave];
				aDate[nCntSave] = nDate;
			}
		}
	}

	// �t�@�C��
	pFile = fopen(SAVE_FILE_NAME, "w");

	// �J����
	if (pFile != NULL)
	{
		for (nCntSave = 0; nCntSave < SAVE_DATE; nCntSave++)
		{
			fprintf(pFile, "%d\n\n", aDate[nCntSave]);	// �|�C���g
		}
		// �t�@�C����
		fclose(pFile);
	}
	// �J���Ȃ�
	else
	{
		printf("�J���܂���ł���\n");
	}
}

//=============================================================================
// �Z�[�u�f�[�^�擾
//=============================================================================
CSave::SAVE *CSave::GetSave(void)
{
	return &m_aSave[0];
}

//=============================================================================
// �N���G�C�g
//=============================================================================
CSave * CSave::Create()
{
	CSave *pSave;

	pSave = new CSave();

	pSave->InitSave();

	return pSave;
}

//=============================================================================
// �R���X�g���N�g
//=============================================================================
CSave::CSave()
{
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CSave::~CSave()
{
}