#include "stdafx.h"
#include "Util.h"
#include <comdef.h>
#include <comutil.h>
#include <atltime.h>
#include <TlHelp32.h>
#include <io.h>
#include <windows.h>
#include <stdio.h>
#include <shellapi.h>

#define STR(x)(LPCTSTR)(x) 
const CString STR_EXCEL2003 = _T("office11");
const CString STR_EXCEL2007 = _T("office12");
const CString STR_EXCEL2010 = _T("office14");
const CString STR_EXCEL2013 = _T("office15");
const CString EXCEL_CUR_VERSION_REG_PATH = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AppPaths\\excel.exe");
#define PATH_MAX 256

#define CMDLINE_SIZE 1024

namespace Util
{

	CString GetModulePath(HMODULE hModule)
	{
		CString path;
		TCHAR modulePath[_MAX_PATH];
		GetModuleFileName(hModule, modulePath, sizeof(modulePath) / sizeof(TCHAR));
		TCHAR *pos = _tcschr(modulePath, _T('\\'));
		if (pos != NULL)
		{
			*pos = _T('\0');
		}
		path = modulePath;
		return path;
	}
	
	CString GetModulePathA()
	{
		CString path;
		TCHAR modulePath[_MAX_PATH];
		GetModuleFileName(NULL, modulePath, sizeof(modulePath) / sizeof(TCHAR));
		path = modulePath;
		int n = path.ReverseFind('\\');
		if (n>0)
		{
			path = path.Left(n+1);
		}
		return path;
	}


}

namespace Env
{
	CString GetEnv(const CString &strEnvName)
	{

		CString strRet;
		TCHAR *pszBuf = 0;
		size_t size = 0;
		errno_t	ret = _tdupenv_s(&pszBuf, &size, (LPCTSTR)strEnvName);
		if (ret == 0)
		{
			strRet = pszBuf;
			delete[] pszBuf;
			pszBuf = 0;
		}
		return strRet;

	}

	CString GetUser()
	{
		return GetEnv(_T("username"));
	}
	CString GetTempDir()
	{
		return GetEnv(_T("TEMP"));
	}
}

