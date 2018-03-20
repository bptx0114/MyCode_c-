#pragma once


#include <string>
#include <map>
#include <deque>
#include <set>
using namespace std;
enum EXCEL_VER{ EXCEL_NONE = 0, EXCEL_2003, EXCEL_2007, EXCEL_2010, EXCEL_2013 };
namespace Util
{
	string ToStr2(int value);
	string GetIniStr(const string &section, const string &keyPrefix, deque<string> &dqValues, const string &file);

	CString GetModulePath(HMODULE hModule);
	CString GetModulePathA();



}

namespace Env
{
	CString GetEnv(const CString &strEnvName);
	CString GetUser();
	CString GetTempDir();
}


