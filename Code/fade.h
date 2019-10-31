//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_


//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
//�t�F�[�h�̃N���X
//=============================================================================
class CFade 
{
public:
	// �t�F�[�h�̏��
	enum FADE
	{
		FADE_NONE = 0,		// �����Ȃ����
		FADE_IN,			// �t�F�[�h�C������
		FADE_OUT,			// �t�F�[�h�A�E�g����
		FADE_MAX
	} ;
	void InitFade();
	void UninitFade(void);
	void UpdateFade(void);
	void DrawFade(void);
	static void SetFade(CManager::MODE modeNext);
	static FADE GetFade(void);

private:
	LPDIRECT3DTEXTURE9 m_pTextureFade;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade;	// ���_�o�b�t�@�ւ̃|�C���^
	static CManager::MODE m_NextMode;		// ���̉�ʁi���[�h�j
	static FADE m_Fade;
	static D3DXCOLOR m_FadeColor;
};
#endif
