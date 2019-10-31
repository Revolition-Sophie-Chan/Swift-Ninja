//=============================================================================
//
// �|���S������[scene.cpp]
// Author : Tanaka Rikiya
//
//=============================================================================

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "renderer.h"
#include "scene.h"
#include "game.h"
#include "manager.h"

//=============================================================================
//�ÓI�����o�ϐ��̏�����
//=============================================================================
CScene *CScene::m_apScene[OBJECT_TYPE_MAX][MAX_TEXTURE] = {};
int CScene::m_NumAll = 0;
int CScene::nCountSlow = 0;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CScene::CScene(OBJECT_TYPE type)
{
	m_bId = 0;
	for (int nCount = 0; nCount < MAX_TEXTURE ; nCount++)
	{
		if (m_apScene[type][nCount] == NULL)
		{
			m_apScene[type][nCount] = this;
			m_NumAll++;
			m_bId = nCount;
			Obj = type;
			break;
		}
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
//�S�ă����[�X
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCntType = 0; nCntType < OBJECT_TYPE_MAX; nCntType++)
	{
		for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
		{
			if (m_apScene[nCntType][nCount] != NULL)
			{
				m_apScene[nCntType][nCount]->Uninit();
				m_apScene[nCntType][nCount] = NULL;
			}
		}
	}
}

//=============================================================================
//�S���X�V
//=============================================================================
void CScene::UpdateAll(void)
{
	CGame *pGame = CGame::GetGame();
	nCountSlow++;

	if (CPlayer::bFinish == false)
	{
		if (CManager::m_Mode != CManager::MODE_PAUSE)
		{
			for (int nCntType = 0; nCntType < OBJECT_TYPE_MAX; nCntType++)
			{
				for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
				{
					if (m_apScene[nCntType][nCount] != NULL)
					{
						m_apScene[nCntType][nCount]->Update();
					}
				}
			}
		}
		else if(CManager::m_Mode == CManager::MODE_PAUSE)
		{
			for (int nCntType = 0; nCntType < OBJECT_TYPE_MAX; nCntType++)
			{
				for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
				{
					if (m_apScene[OBJECT_TYPE_UI][nCount] != NULL)
					{
						m_apScene[OBJECT_TYPE_UI][nCount]->Update();
					}
				}
			}
		}
	}
	else
	{	//�I�����ɃX���[�ɂȂ�
		if (nCountSlow % 3==0)
		{
			for (int nCntType = 0; nCntType < OBJECT_TYPE_MAX; nCntType++)
			{
				for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
				{
					if (m_apScene[nCntType][nCount] != NULL)
					{
						m_apScene[nCntType][nCount]->Update();
					}
				}
			}
		}
	}
}

//=============================================================================
//�S�`��
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCntType = 0; nCntType < OBJECT_TYPE_MAX; nCntType++)
	{
		for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
		{
			if (m_apScene[nCntType][nCount] != NULL)
			{
				m_apScene[nCntType][nCount]->Draw();
			}
		}
	}
}

//=============================================================================
//�����[�X
//=============================================================================
void CScene::Release(void)
{
	OBJECT_TYPE type = Obj;
	m_nID = m_bId;
	if (m_apScene[type][m_bId] != NULL)
	{
		m_NumAll--;
		m_apScene[type][m_nID] = NULL;
		delete m_apScene[type][m_nID];
	}
}

//=============================================================================
//�I�u�W�F�N�g�^�C�v�̎擾
//=============================================================================
CScene::OBJECT_TYPE  CScene::GetObjType(void)
{
	return Obj;
}

//=============================================================================
//�I�u�W�F�N�g�^�C�v�̐ݒ�
//=============================================================================
void  CScene::SetObjType(OBJECT_TYPE Set)
{
	Obj = Set;
}

//=============================================================================
//�V�[���擾
//=============================================================================
CScene *CScene::GetScene(int TypeObj, OBJECT_TYPE type)
{
	return m_apScene[type][TypeObj];
}