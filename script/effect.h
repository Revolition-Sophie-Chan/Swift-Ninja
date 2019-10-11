
//=============================================================================
//
// �G�t�F�N�g�̏���[Effect.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_EFFECT (3)

//=============================================================================
//�N���X
//=============================================================================
class CEffect : public CScene2D 
{
public:
	CEffect(OBJECT_TYPE type);
	 ~CEffect();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CEffect *Create(D3DXVECTOR3 Effectpos, D3DXCOLOR Effectcol, D3DXVECTOR3 Effectmove,float Size,int Effect_Number,int EffectLife);
	 D3DXCOLOR GetEffectColer(void);
private:

	int m_nLife;
	//VERTEX_2D m_aVertex[4];
	static LPDIRECT3DTEXTURE9 m_pTextureEffect[MAX_EFFECT];//�e�N�X�`���ւ̃|�C���^
	//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;//���_�o�b�t�@�ւ̃|�C���^
	D3DXCOLOR m_col;
	int m_nCountRot = 0;
};
#endif