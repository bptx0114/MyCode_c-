
// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef int(*Instru_Init)(CString&, CString&, CString&);




// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestDlg 对话框



CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	client = NULL;
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTestDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CTestDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CTestDlg::OnBnClickedButton9)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SetTimer(1, 100, NULL);
	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef int(*Instru_Init)(CString&, CString&, CString&);

void CTestDlg::OnBnClickedButton1()
{
	//ATL_dll();

	LoadLibrary_dll();

}

void CTestDlg::ATL_dll()
{
	HRESULT hr = interfacePtr.CreateInstance(__uuidof(ICInterfaceIO));
	BSTR* sRs = NULL;
	int n = 0;
	CString str1(_T("PAN")), str2(_T(" BO"));
	CString str;
	if (SUCCEEDED(hr))
	{
		interfacePtr->Test((LPCTSTR)str1, (LPCTSTR)str2, sRs);
	}
	int n3 = GetLastError();
}



void CTestDlg::LoadLibrary_dll()
{
	CString strPath(Util::GetModulePathA() + _T("MFCLibrary.dll"));

	HINSTANCE hDll = LoadLibrary(strPath);
	CString str1(_T("pan")), str2(_T(" bo")), str;

	if (hDll != NULL)
	{
		Instru_Init InstruFun;
		InstruFun = (Instru_Init)GetProcAddress(hDll, "Instru_Init");
		int result = -1;
		if (InstruFun != NULL)
		{
			result = InstruFun(str1, str2, str);
		}
		else
		{
			int erro = GetLastError();
			AfxMessageBox(_T("Didn't find the Function"));
			return;
		}
	}
	else
	{
		int erro = GetLastError();
		AfxMessageBox(_T("Didn't find the dll"));
		return;
	}
}
#include "SelectServer.h"
void CTestDlg::OnBnClickedButton2()
{
	CSelectServer srv;
	srv.DoTask();
}


void CTestDlg::OnBnClickedButton3()
{

	client->DoWork();

}


void CTestDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	client->SendData();

}


void CTestDlg::OnBnClickedButton5()
{
	HINSTANCE hAddDll = NULL;
	typedef int (WINAPI*AddProc)(int a, int b);//函数原型定义
	AddProc add;
	if (hAddDll == NULL)
	{
		hAddDll = ::LoadLibrary(_T("Add.dll"));//加载dll
	}
	add = (AddProc)::GetProcAddress(hAddDll, "add");//获取函数add地址

	int a = 1;
	int b = 2;
	int c = add(a, b);//调用函数
	CString tem;
	tem.Format(_T("%d+%d=%d"), a, b, c);
	AfxMessageBox(tem);

}


HINSTANCE hinst = NULL;
void CTestDlg::OnBnClickedButton6()
{

	typedef BOOL(CALLBACK *inshook)(); //函数原型定义
	inshook insthook;

	hinst = LoadLibrary(_T("Hook.dll"));//加载dll文件
	if (hinst == NULL)
	{
		AfxMessageBox(_T("no Hook.dll!"));
		return;
	}
	insthook = ::GetProcAddress(hinst, "InstallHook");//获取函数地址
	if (insthook == NULL)
	{
		AfxMessageBox(_T("func not found!"));
		return;
	}
	insthook();//开始HOOK
}


void CTestDlg::OnBnClickedButton7()
{
	if (hinst == NULL)
	{
		return;
	}
	typedef BOOL(CALLBACK *UnhookProc)(); //函数原型定义
	UnhookProc UninstallHook;

	UninstallHook = ::GetProcAddress(hinst, "UninstallHook");//获取函数地址
	if (UninstallHook != NULL)
	{
		UninstallHook();
	}
	if (hinst != NULL)
	{
		::FreeLibrary(hinst);
	}

}


void CTestDlg::OnBnClickedButton8()
{
	
}



#include "YCom232.h"
CYCom232 ycom232;
void CTestDlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	

	BYTE bytesize = 0;
	BYTE parity = NOPARITY;
	BYTE stopbits = ONESTOPBIT;
	DWORD rate = CBR_57600;
	if (ycom232.OpenCom("COM3", rate, bytesize, parity, stopbits))
	{	
		for (int i=0;i<10000;++i)
		{
			unsigned buf_i = 0;
			unsigned char data[2];
			data[0] = 0x0A;
			data[1] = 0x0B;
			ycom232.SendData(data, 2, 50);
			Sleep(1000);
		}

	}





}


void CTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	unsigned buf_i = 0;
	memset((char*)ycom232.RxBuf, 0, 2048);
	char *recvData = new char[2048];
	//for (int i = 0;i < 50;++i)
	//{
	//	buf_i = ycom232.ReadData();
	//	if (ycom232.RxBuf[i] != 0x00)
	//	{
	//		recvData += (char)ycom232.RxBuf[i];
	//	}
	//}
	buf_i = ycom232.ReadData();
	CDialogEx::OnTimer(nIDEvent);
}
