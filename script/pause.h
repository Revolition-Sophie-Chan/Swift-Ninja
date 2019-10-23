//=============================================================================
//
// �^�C�g���̏���[Pause.h]
// Author�Ftanaka rikiya
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#define _CRT_SECURE_NO_WARNINGS

//�C���N���[�h�t�@�C��
#include "main.h"
#include "manager.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define PAUSESELECT (3)

class CTexture;
//=============================================================================
//�N���X
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
	bool bSelect;
	CTexture *m_pPauseTexture[PAUSESELECT];
	int StateCount;
	static PAUSE_STATE PauseState;


};
#endif