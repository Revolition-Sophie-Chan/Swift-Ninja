//=============================================================================
//
// �����_���[����[renderer.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _RENDERE_H_
#define _RENDERE_H_

#include"main.h"
#include"fade.h"
#include"player.h"

//=============================================================================
//�\����
//=============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;//�e�N�X�`�����W
} VERTEX_2D;
//=============================================================================
//�N���X
//=============================================================================
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void UpDate(void);
	void Draw(void);
#ifdef _DEBUG
	//

	void DrawFPS(void);
#endif

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; };

private:
	LPD3DXFONT m_pFont = NULL;
	int m_FPS;
	LPDIRECT3D9 m_pD3D;				//Direct3D�I�u�W�F�N�g�̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;	//Direct3D�f�o�C�X�̃|�C���^
	CFade *m_Fade;

	static CPlayer *m_Player;
};

#endif