
// CameraViewDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


// CCameraViewDlg �Ի���



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
// CCameraViewDlg ��Ϣ�������

BOOL CCameraViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCameraViewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
