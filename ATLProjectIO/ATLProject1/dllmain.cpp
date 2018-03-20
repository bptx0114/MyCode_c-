// dllmain.cpp : DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "ATLProject1_i.h"
#include "dllmain.h"
#include "xdlldata.h"

CATLProject1Module _AtlModule;

class CATLProject1App : public CWinApp
{
public:

// 重写
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CATLProject1App, CWinApp)
END_MESSAGE_MAP()

CATLProject1App theApp;

BOOL CATLProject1App::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, NULL))
		return FALSE;
#endif
	return CWinApp::InitInstance();
}

int CATLProject1App::ExitInstance()
{
	return CWinApp::ExitInstance();
}
