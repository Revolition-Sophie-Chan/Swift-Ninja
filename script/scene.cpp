//=============================================================================
//
// ポリゴン処理[scene.cpp]
// Author：tanaka rikiya
//
//=============================================================================
#include"renderer.h"
#include"scene.h"
#include"game.h"
#include "manager.h"

CScene *CScene::m_apScene[OBJECT_TYPE_MAX][MAX_TEXTURE] = {};
int CScene::m_NumAll = 0;
int CScene::nCountSlow = 0;
//============================================================================================
//こンストラクタ
//============================================================================================
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
//============================================================================================
//デストラクタ
//============================================================================================
CScene::~CScene()
{
}
//=============================================================================
// 全てリリース
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
// 全部更新
//=============================================================================
void CScene::UpdateAll(void)
{
	CGame *pGame = CGame::GetGame();
	nCountSlow++;
	if (CPlayer::bFinish == false)
	{
		if (pGame->bDamage == false && pGame->bPause == false || CManager::m_Mode != CManager::MODE_GAME)
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
	else
	{
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
// 全描画
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
// 
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

CScene::OBJECT_TYPE  CScene::GetObjType(void)
{
	return Obj;
}

void  CScene::SetObjType(OBJECT_TYPE Set)
{
	Obj = Set;
}
CScene *CScene::GetScene(int TypeObj, OBJECT_TYPE type)
{
	return m_apScene[type][TypeObj];
}