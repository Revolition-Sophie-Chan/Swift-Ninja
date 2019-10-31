//=============================================================================
//
// �|�[�Y��ʂ̏���[pause.h]
// Author : Tanaka Rikiya
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
//�C���N���[�h
//=============================================================================
#include "main.h"
#include "manager.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define PAUSESELECT (3)

//=============================================================================
//�O���錾
//=============================================================================
class CTexture;

//=============================================================================
//�|�[�Y�̃N���X
//=============================================================================
class CPause
{
public:
	enum PAUSE_STATE
	{
		PAUSESTATE_CONTINUE,
		PAUSESTATE_RETRY,
		PAUSESTATE_QUIT,
		PAUSESTATE_MAX
	};

	CPause();
	~CPause();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetDraw(bool bDraw);
	static CPause *Create();

	static PAUSE_STATE GetPauseState(); 
	static void SetPauseState(PAUSE_STATE state);


private:
	void SetSelectSize(int Size);

	CTexture *m_pPauseTexture[PAUSESELECT];


	static PAUSE_STATE PauseState;
	int		StateCount;
	float	Size_X;
	float	Size_Y;
	bool	bSelect;
	bool	bSize;
};
#endif