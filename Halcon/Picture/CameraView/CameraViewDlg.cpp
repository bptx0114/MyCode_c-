
// CameraViewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CameraView.h"
#include "CameraViewDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "halconcpp.h"
using namespace HalconCpp;

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


// CCameraViewDlg 对话框



CCameraViewDlg::CCameraViewDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CCameraViewDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCameraViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCameraViewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_VIEW, &CCameraViewDlg::OnBnClickedBtnView)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CCameraViewDlg::OnBnClickedBtnClose)
END_MESSAGE_MAP()


HObject  ho_Image;
HTuple  hv_AcqHandle, hv_Width, hv_Height, hv_WindowHandle;
// CCameraViewDlg 消息处理程序

BOOL CCameraViewDlg::OnInitDialog()
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


	OpenFramegrabber("DirectShow", 1, 1, 0, 0, 0, 0, "default", 8, "rgb", -1, "false",
		"default", "[0] FULL HD 1080P Webcam", 0, -1, &hv_AcqHandle);
	GrabImageStart(hv_AcqHandle, -1);
	GrabImageAsync(&ho_Image, hv_AcqHandle, -1);
	GetImageSize(ho_Image, &hv_Width, &hv_Height);
	SetWindowAttr("background_color", "black");

	HWND hWnd = GetDlgItem(IDC_PICTURE_VIEW)->m_hWnd;
	LONG halconHwnd = (LONG)hWnd;
	CRect rect;
	GetDlgItem(IDC_PICTURE_VIEW)->GetClientRect(&rect);
	HTuple nWidth, nHeight;
	nWidth[0] = rect.Width();
	nHeight[0] = rect.Height();	
	OpenWindow(0, 0, nWidth[0], nHeight[0], halconHwnd, "", "", &hv_WindowHandle);


	HDevWindowStack::Push(hv_WindowHandle);
	if (HDevWindowStack::IsOpen())
		DispObj(ho_Image, HDevWindowStack::GetActive());

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCameraViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCameraViewDlg::OnPaint()
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
HCURSOR CCameraViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCameraViewDlg::OnBnClickedBtnView()
{
	SetTimer(1, 40, NULL);
}


void CCameraViewDlg::OnTimer(UINT_PTR nIDEvent)
{
	GrabImageAsync(&ho_Image, hv_AcqHandle, -1);

	if (HDevWindowStack::IsOpen())
		DispObj(ho_Image, HDevWindowStack::GetActive());

	CDialogEx::OnTimer(nIDEvent);
}


void CCameraViewDlg::OnBnClickedBtnClose()
{
	//CloseFramegrabber(hv_AcqHandle);
	KillTimer(1);
}
