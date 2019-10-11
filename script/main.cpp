//=============================================================================
//
// メイン処理[main.cpp]
// Author：tanaka rikiya
//
//=============================================================================
#include"main.h"
#include"manager.h"
#include"scene.h"
#include "scene2D.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define CLASS_NAME	"WindowClass"		//ウィンドウクラスの名前
#define WINDOW_NAME	"Swift忍者"	//キャプション

//=============================================================================
//プロトタイプ宣言
//=============================================================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wPARAM, LPARAM lPARAM);

//=============================================================================
//グローバル変数
//=============================================================================
#ifdef _DEBUG
int g_nCountFPS = 0;
#endif
//=============================================================================
//メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	CManager *pManager;

		RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		//指定されたクライアント領域を確保するための計算を行う
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		WNDCLASSEX wcex =
		{
			sizeof(WNDCLASSEX),				//WNDCCLASSEXのメモリサイズを指定
			CS_CLASSDC,						//表示ウィンドウのスタイルを指定
			WindowsProc,					//ウィンドウプロシージャもアドレス(関数名）を指定
			0,								//通常は使わないので0指定
			0,								//通常は使わないので0指定
			hInstance,						//Windowsの引数のインスタンスハンドル指定
			LoadIcon(NULL,IDI_APPLICATION),	//タスクバーに使用するアイコン
			LoadCursor(NULL,IDC_ARROW),		//使用するマウスカーソル
			(HBRUSH)(COLOR_WINDOW + 1),		//ウィンドウクライアント領域の色指定
			NULL,							//メニューを指定
			CLASS_NAME,						//ウィンドウクラスの名前
			LoadIcon(NULL,IDI_APPLICATION),	//小さいアイコンの指定 左上のやつ
		};

		HWND hWnd;	//ウィンドウハンドル(識別子)
		MSG msg;	//メッセージを格納する変数
		DWORD dwCurrentTime;//現在時間
		DWORD dwExclastTime;//最後に処理した時間

		DWORD dwFrameCount;//現在時間
		DWORD dwFPSLastTime;//最後に処理した時間

		//ウィンドウクラスの登録
		RegisterClassEx(&wcex);

		//ウィンドウの生成
		hWnd = CreateWindowEx(0,	//拡張ウィンドウスタイル
			CLASS_NAME,				//ウィンドウクラス名
			WINDOW_NAME,			//ウィンドウの名前
			WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル
			CW_USEDEFAULT,			//ウィンドウ左上X座標
			CW_USEDEFAULT,			//ウィンドウ左上Y座標
			(rect.right - rect.left),		//ウィンドウの幅
			(rect.bottom - rect.top),		//ウィンドウの高さ
			NULL,					//親ウィンドウのハンドル
			NULL,					//メニューもしくは子ウィンドウⅡ
			hInstance,				//インスタンスハンドル
			NULL);					//ウィンドウ作成データ

		pManager = new CManager;
		//初期化処理
		if (FAILED(pManager->Init(hInstance,hWnd, TRUE)))//ここをFALSEにするとフルスク
		{
			return-1;	//失敗したら抜ける
		}



		//ウィンドウの表示
		ShowWindow(hWnd, nCmdShow);	//指定されたウィンドウの表示設定
		UpdateWindow(hWnd);			//ウィンドウのクライアント領域更新

		dwCurrentTime = 0;
		dwExclastTime = timeGetTime();//現在時間を取得
		dwFrameCount = 0;
		dwFPSLastTime = timeGetTime();

	//メッセージループ（メッセージキューからメッセージを取得
		while (1)//while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{//Window処理
				if (msg.message == WM_QUIT)
				{
					break;
				}
				else
				{
					//メッセージの翻訳と送出
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{//DirectXの処理

				if ((dwCurrentTime - dwFPSLastTime) >= 500)
				{
#ifdef _DEBUG
					g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
					dwFPSLastTime = dwCurrentTime;
					dwFrameCount = 0;
#endif
				}
				dwCurrentTime = timeGetTime();//
				if ((dwCurrentTime - dwExclastTime) >= (1000 / 60))//1/60秒ごと実行
				{
					dwExclastTime = dwCurrentTime;//処理した時間を保存
					//更新処理
					pManager->Update();
					//描画処理
					pManager->Draw();
					dwFrameCount++;
				}
			}
		}
		//終了処理
		if (pManager != NULL)
		{
			pManager->Uninit();
		
			delete pManager;
			pManager = NULL;
		}
		//ウィンドウクラスの登録と解除
		UnregisterClass(CLASS_NAME, wcex.hInstance);
		return (int)msg.wParam;
	
}
//=============================================================================
//ウィンドウプロシージャ関数
//=============================================================================
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
		//右上の罰押したとき
	case WM_CLOSE:

		DestroyWindow(hWnd);
		return 0;//強制的に抜ける
		break;

		//ウィンドウ破棄メッセージ
	case WM_DESTROY: //ウィンドウを終了する（消してはいけない）
					 //WM_QUIT;//メッセージを返す
		PostQuitMessage(0);//quitを発生させる
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE://escキーが押された
					   //ウィンドウを破棄
			DestroyWindow(hWnd);
			break;
		}
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//既定の処理を提供 
}

#ifdef _DEBUG
int GetFPS(void)
{
	return g_nCountFPS;
}
#endif

//
////マネージャの生成
//pManager = new CManager;
//pManager->Init()
//
////メッセージループ
//pManager->Update();
//pManager->Draw();
//


