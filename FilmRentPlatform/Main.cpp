#include "stdafx.h"
#include "main_frame.h"

#include <atlbase.h>
CComModule _Module;
#include <atlwin.h>
#include <crtdbg.h>

#ifdef _DEBUG    
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)    
#else    
#define DEBUG_CLIENTBLOCK    
#endif    
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

#if defined(WIN32) && !defined(UNDER_CE)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
#else
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nCmdShow)
#endif
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CPaintManagerUI::SetInstance(hInstance);

	HINSTANCE hInstRich = ::LoadLibrary(_T("Riched20.dll"));

	::CoInitialize(NULL);
	::OleInitialize(NULL);

	_Module.Init(0, hInstance);

#if defined(WIN32) && !defined(UNDER_CE)
	HRESULT Hr = ::CoInitialize(NULL);
#else
	HRESULT Hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif
	if (FAILED(Hr)) return 0;

	MainFrame* pFrame = new MainFrame();
	if (pFrame == NULL) return 0;
#if defined(WIN32) && !defined(UNDER_CE)
	pFrame->Create(NULL, _T("��Ӱ����ϵͳ"), UI_WNDSTYLE_FRAME | WS_CLIPCHILDREN, WS_EX_WINDOWEDGE, 0, 0, 850, 446);
#else
	pFrame->Create(NULL, _T("��Ӱ����ϵͳ"), UI_WNDSTYLE_DIALOG, WS_EX_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#endif
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();
	CPaintManagerUI::Term();

	_Module.Term();

	::OleUninitialize();
	::CoUninitialize();

	::FreeLibrary(hInstRich);

	return 0;
}