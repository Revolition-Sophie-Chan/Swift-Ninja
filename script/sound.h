//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
//=============================================================================
//�N���X
//=============================================================================

class CSound
{
public:
	//=============================================================================
	// �T�E���h�t�@�C��
	//=============================================================================
	typedef enum
	{
		SOUND_LABEL_TITLE = 0,		// BGM�^�C�g��	
		SOUND_LABEL_BATTLE,			// BGM�퓬		
		SOUND_LABEL_RANKING,		// BGM�����L���O
		SOUND_LABEL_SE_KO,			// ���j			
		SOUND_LABEL_SE_JUMP,		// �W�����v		
		SOUND_LABEL_SE_ATK,			// �U��			
		SOUND_LABEL_SE_BOMB,		// ����			
		SOUND_LABEL_SE_FEVER,		// �t�B�[�o�[	
		SOUND_LABEL_SE_FEVER2,		// �t�B�[�o�[2	
		SOUND_LABEL_MAX,
	} SOUND_LABEL;
	//=============================================================================
	// �p�����[�^�\���̒�`
	//=============================================================================
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "Data/Sound/BGM/title.wav", -1 },		// BGM0(-1�ŌJ��Ԃ��j
		{ "Data/Sound/BGM/game.wav", -1 },		// BGM1
		{ "Data/Sound/BGM/ranking.wav", -1 },	// BGM2
		{ "Data/Sound/SE/bomb0.wav", 0 },	// ���j
		{ "Data/Sound/SE/Jump.wav", 0 },		// �W�����v
		{ "Data/Sound/SE/Atk01.wav", 0 },		// �U��
		{ "Data/Sound/SE/Explosion.wav", 0 },	// ���j
		{ "Data/Sound/SE/Fever.wav", 0 },	// �t�B�[�o�[�˓�
		{ "Data/Sound/SE/Fever2.wav", 0 },	// �t�B�[�o�[�˓�
	};

	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);

	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
};
#endif
