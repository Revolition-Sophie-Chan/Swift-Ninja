
//=============================================================================
//
// �|�C���^�[�̏���[Here.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _HERE_H_
#define _HERE_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//�N���X
//=============================================================================
class CHere : public CScene2D 
{
public:
	CHere(OBJECT_TYPE type);
	 ~CHere();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CHere *Create();

private:
	bool bHere;
	int m_nLife;
	static LPDIRECT3DTEXTURE9 m_pTextureHere;//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_Playerpos;
};
#endif