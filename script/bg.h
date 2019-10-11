
//=============================================================================
//
// �w�i�̏���[Bg.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//�}�N����`
//=============================================================================
//=============================================================================
//�N���X
//=============================================================================
class CBg : public CScene2D 
{
public:
	CBg(OBJECT_TYPE type);
	 ~CBg();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CBg *Create(D3DXVECTOR3 BGpos);
private:

	int m_nLife;
	//VERTEX_2D m_aVertex[4];
	static LPDIRECT3DTEXTURE9 m_pTextureBg;//�e�N�X�`���ւ̃|�C���^
	//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	int m_nCountRot = 0;
};
#endif