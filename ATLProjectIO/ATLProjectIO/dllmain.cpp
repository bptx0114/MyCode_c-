// dllmain.cpp : DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "ATLProjectIO_i.h"
#include "dllmain.h"
#include "compreg.h"
#include "xdlldata.h"

CATLProjectIOModule _AtlModule;

class CATLProjectIOApp : public CWinApp
{
public:

// 重写
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CATLProjectIOApp, CWinApp)
END_MESSAGE_MAP()

CATLProjectIOApp theApp;

BOOL CATLProjectIOApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
	if (!PrxDllMain(m_hInstance, DLL_PROCESS_ATTACH, NULL))
		return FALSE;
#endif
	return CWinApp::InitInstance();
}

int CATLProjectIOApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
