//=============================================================================
//
// ���C������[main.cpp]
// Author�Ftanaka rikiya
//
//=============================================================================
#include"main.h"
#include"manager.h"
#include"scene.h"
#include "scene2D.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define CLASS_NAME	"WindowClass"		//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME	"Swift�E��"	//�L���v�V����

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wPARAM, LPARAM lPARAM);

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
#ifdef _DEBUG
int g_nCountFPS = 0;
#endif
//=============================================================================
//���C���֐�
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	CManager *pManager;

		RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		//�w�肳�ꂽ�N���C�A���g�̈���m�ۂ��邽�߂̌v�Z���s��
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		WNDCLASSEX wcex =
		{
			sizeof(WNDCLASSEX),				//WNDCCLASSEX�̃������T�C�Y���w��
			CS_CLASSDC,						//�\���E�B���h�E�̃X�^�C�����w��
			WindowsProc,					//�E�B���h�E�v���V�[�W�����A�h���X(�֐����j���w��
			0,								//�ʏ�͎g��Ȃ��̂�0�w��
			0,								//�ʏ�͎g��Ȃ��̂�0�w��
			hInstance,						//Windows�̈����̃C���X�^���X�n���h���w��
			LoadIcon(NULL,IDI_APPLICATION),	//�^�X�N�o�[�Ɏg�p����A�C�R��
			LoadCursor(NULL,IDC_ARROW),		//�g�p����}�E�X�J�[�\��
			(HBRUSH)(COLOR_WINDOW + 1),		//�E�B���h�E�N���C�A���g�̈�̐F�w��
			NULL,							//���j���[���w��
			CLASS_NAME,						//�E�B���h�E�N���X�̖��O
			LoadIcon(NULL,IDI_APPLICATION),	//�������A�C�R���̎w�� ����̂��
		};

		HWND hWnd;	//�E�B���h�E�n���h��(���ʎq)
		MSG msg;	//���b�Z�[�W���i�[����ϐ�
		DWORD dwCurrentTime;//���ݎ���
		DWORD dwExclastTime;//�Ō�ɏ�����������

		DWORD dwFrameCount;//���ݎ���
		DWORD dwFPSLastTime;//�Ō�ɏ�����������

		//�E�B���h�E�N���X�̓o�^
		RegisterClassEx(&wcex);

		//�E�B���h�E�̐���
		hWnd = CreateWindowEx(0,	//�g���E�B���h�E�X�^�C��
			CLASS_NAME,				//�E�B���h�E�N���X��
			WINDOW_NAME,			//�E�B���h�E�̖��O
			WS_OVERLAPPEDWINDOW,	//�E�B���h�E�X�^�C��
			CW_USEDEFAULT,			//�E�B���h�E����X���W
			CW_USEDEFAULT,			//�E�B���h�E����Y���W
			(rect.right - rect.left),		//�E�B���h�E�̕�
			(rect.bottom - rect.top),		//�E�B���h�E�̍���
			NULL,					//�e�E�B���h�E�̃n���h��
			NULL,					//���j���[�������͎q�E�B���h�E�U
			hInstance,				//�C���X�^���X�n���h��
			NULL);					//�E�B���h�E�쐬�f�[�^

		pManager = new CManager;
		//����������
		if (FAILED(pManager->Init(hInstance,hWnd, TRUE)))//������FALSE�ɂ���ƃt���X�N
		{
			return-1;	//���s�����甲����
		}



		//�E�B���h�E�̕\��
		ShowWindow(hWnd, nCmdShow);	//�w�肳�ꂽ�E�B���h�E�̕\���ݒ�
		UpdateWindow(hWnd);			//�E�B���h�E�̃N���C�A���g�̈�X�V

		dwCurrentTime = 0;
		dwExclastTime = timeGetTime();//���ݎ��Ԃ��擾
		dwFrameCount = 0;
		dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v�i���b�Z�[�W�L���[���烁�b�Z�[�W���擾
		while (1)//while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{//Window����
				if (msg.message == WM_QUIT)
				{
					break;
				}
				else
				{
					//���b�Z�[�W�̖|��Ƒ��o
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{//DirectX�̏���

				if ((dwCurrentTime - dwFPSLastTime) >= 500)
				{
#ifdef _DEBUG
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
					dwFPSLastTime = dwCurrentTime;
					dwFrameCount = 0;
#endif
				}
				dwCurrentTime = timeGetTime();//
				if ((dwCurrentTime - dwExclastTime) >= (1000 / 60))//1/60�b���Ǝ��s
				{
					dwExclastTime = dwCurrentTime;//�����������Ԃ�ۑ�
					//�X�V����
					pManager->Update();
					//�`�揈��
					pManager->Draw();
					dwFrameCount++;
				}
			}
		}
		//�I������
		if (pManager != NULL)
		{
			pManager->Uninit();
		
			delete pManager;
			pManager = NULL;
		}
		//�E�B���h�E�N���X�̓o�^�Ɖ���
		UnregisterClass(CLASS_NAME, wcex.hInstance);
		return (int)msg.wParam;
	
}
//=============================================================================
//�E�B���h�E�v���V�[�W���֐�
//=============================================================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
		//�E��̔��������Ƃ�
	case WM_CLOSE:

		DestroyWindow(hWnd);
		return 0;//�����I�ɔ�����
		break;

		//�E�B���h�E�j�����b�Z�[�W
	case WM_DESTROY: //�E�B���h�E���I������i�����Ă͂����Ȃ��j
					 //WM_QUIT;//���b�Z�[�W��Ԃ�
		PostQuitMessage(0);//quit�𔭐�������
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE://esc�L�[�������ꂽ
					   //�E�B���h�E��j��
			DestroyWindow(hWnd);
			break;
		}
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//����̏������ 
}

#ifdef _DEBUG
int GetFPS(void)
{
	return g_nCountFPS;
}
#endif

//
////�}�l�[�W���̐���
//pManager = new CManager;
//pManager->Init()
//
////���b�Z�[�W���[�v
//pManager->Update();
//pManager->Draw();
//


