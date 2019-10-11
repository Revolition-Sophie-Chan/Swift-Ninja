//=============================================================================
//
// サウンド処理 [sound.h]
// Author : tanaka rikiya
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
//=============================================================================
//クラス
//=============================================================================

class CSound
{
public:
	//=============================================================================
	// サウンドファイル
	//=============================================================================
	typedef enum
	{
		SOUND_LABEL_TITLE = 0,		// BGMタイトル	
		SOUND_LABEL_BATTLE,			// BGM戦闘		
		SOUND_LABEL_RANKING,		// BGMランキング
		SOUND_LABEL_SE_KO,			// 撃破			
		SOUND_LABEL_SE_JUMP,		// ジャンプ		
		SOUND_LABEL_SE_ATK,			// 攻撃			
		SOUND_LABEL_SE_BOMB,		// 爆発			
		SOUND_LABEL_SE_FEVER,		// フィーバー	
		SOUND_LABEL_SE_FEVER2,		// フィーバー2	
		SOUND_LABEL_MAX,
	} SOUND_LABEL;
	//=============================================================================
	// パラメータ構造体定義
	//=============================================================================
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	// 各音素材のパラメータ
	SOUNDPARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "Data/Sound/BGM/title.wav", -1 },		// BGM0(-1で繰り返し）
		{ "Data/Sound/BGM/game.wav", -1 },		// BGM1
		{ "Data/Sound/BGM/ranking.wav", -1 },	// BGM2
		{ "Data/Sound/SE/bomb0.wav", 0 },	// 撃破
		{ "Data/Sound/SE/Jump.wav", 0 },		// ジャンプ
		{ "Data/Sound/SE/Atk01.wav", 0 },		// 攻撃
		{ "Data/Sound/SE/Explosion.wav", 0 },	// 撃破
		{ "Data/Sound/SE/Fever.wav", 0 },	// フィーバー突入
		{ "Data/Sound/SE/Fever2.wav", 0 },	// フィーバー突入
	};

	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);

	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ
};
#endif
