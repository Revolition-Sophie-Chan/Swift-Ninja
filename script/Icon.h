
//=============================================================================
//
// �A�C�R���̏���[Icon.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _ICON_H_
#define _ICON_H_

//=============================================================================
// �C���N���[�h
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
class CIcon : public CScene2D 
{
public:
	CIcon(OBJECT_TYPE type);
	 ~CIcon();
	 void Init();
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	 static HRESULT Load(void);
	 static void Unload(void);
	 static CIcon *Create(D3DXVECTOR3 Iconpos);

private:
	static LPDIRECT3DTEXTURE9 m_pTextureIcon;//�e�N�X�`���ւ̃|�C���^
	bool bFlag;
};
#endif