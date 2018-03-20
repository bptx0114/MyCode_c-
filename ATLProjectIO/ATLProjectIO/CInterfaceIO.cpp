// CInterfaceIO.cpp : CCInterfaceIO µÄÊµÏÖ

#include "stdafx.h"
#include "CInterfaceIO.h"


// CCInterfaceIO



STDMETHODIMP CCInterfaceIO::Test(BSTR Arg1, BSTR Arg2, BSTR* Output, VARIANT_BOOL* Rst)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString str1(Arg1);
	CString str2(Arg2);
	CString str(str1+str2);
	//Output = str.AllocSysString();

	return S_OK;
}
