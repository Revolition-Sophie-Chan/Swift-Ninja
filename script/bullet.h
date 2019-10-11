
//=============================================================================
//
// �e�̏���[bullet.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define HITSIZE_X (200)
#define HITSIZE_Y (200)

//=============================================================================
//�N���X
//=============================================================================
class CBullet : public CScene2D 
{
public:
	CBullet(OBJECT_TYPE type);
	 ~CBullet();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CBullet *Create();
private:
	bool CollisionTest(D3DXVECTOR3 pos);
	void MakeEffect(void);
	void MakeExplosion(void);
	int m_nLife;
	//VERTEX_2D m_aVertex[4];
	static LPDIRECT3DTEXTURE9 m_pTextureBullet[MAX_TEXTURE];//�e�N�X�`���ւ̃|�C���^
	//LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon;//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_move;
	int m_nCountRot = 0;
	float m_fRot = D3DX_PI*0.25f;
	float m_fposSize = 100.0f;
};
#endif