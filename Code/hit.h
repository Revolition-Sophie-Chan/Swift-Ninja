//=============================================================================
//
// ���j���o�̏���[hit.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _HIT_H_
#define _HIT_H_

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_HIT		(4)

//=============================================================================
//���j���o�N���X
//=============================================================================
class CHit : public CScene2D
{
public:
	CHit(OBJECT_TYPE type);
	 ~CHit();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CHit *Create(D3DXCOLOR Hitcol,int type, int nLife);

private:

	static LPDIRECT3DTEXTURE9 m_pTexturehit[MAX_HIT];//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	int m_nLife;
};
#endif