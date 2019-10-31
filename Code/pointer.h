//=============================================================================
//
// �|�C���^�[�̏���[pointer.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _POINTER_H_
#define _POINTER_H_

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//���̃N���X
//=============================================================================
class CPointer : public CScene2D 
{
public:
	CPointer(OBJECT_TYPE type);
	 ~CPointer();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 void RotSet(float fRot);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CPointer *Create();

private:
	static LPDIRECT3DTEXTURE9 m_pTexturePointer;//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_Playerpos;
	int m_nLife;
	float PointRot;
};
#endif