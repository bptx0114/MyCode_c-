
// PictureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Picture.h"
#include "PictureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "HalconCpp.h"
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


// CPictureDlg 对话框



CPictureDlg::CPictureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPictureDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPictureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_READ, &CPictureDlg::OnBnClickedBtnRead)
	ON_BN_CLICKED(IDC_BTN_VIEW, &CPictureDlg::OnBnClickedBtnView)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CPictureDlg::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// CPictureDlg 消息处理程序

BOOL CPictureDlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPictureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPictureDlg::OnPaint()
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
HCURSOR CPictureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CPictureDlg::ComputeColorTabalLength(int nBitCount)
{
	int colorTableLength;
	switch (nBitCount) {
	case 1:
		colorTableLength = 2;
		break;
	case 4:
		colorTableLength = 16;
		break;
	case 8:
		colorTableLength = 256;
		break;
	case 16:
	case 24:
	case 32:
		colorTableLength = 0;
		break;
	default:
		ASSERT(FALSE);
	}


	return colorTableLength;
}

void CPictureDlg::OnBnClickedBtnRead()
{
	CFile file;
	if (!file.Open("E:\\Code\\MyCode_cpp\\Halcon\\Picture\\all.bmp", CFile::modeRead))
		return;

	BITMAPFILEHEADER bmfh;
	try {

		//读取BITMAPFILEHEADER结构到变量bmfh中
		int nCount = file.Read((LPVOID)&bmfh, sizeof(BITMAPFILEHEADER));



		//为m_lpDib分配空间，读取DIB进内存

		m_lpDib = new BYTE[file.GetLength() - sizeof(BITMAPFILEHEADER)];

		file.Read(m_lpDib, file.GetLength() - sizeof(BITMAPFILEHEADER));

		//m_lpBmpInfoHead位置为m_lpDib起始位置
		m_lpBmpInfoHead = (LPBITMAPINFOHEADER)m_lpDib;

		//为成员变量赋值
		m_imgWidth = m_lpBmpInfoHead->biWidth;
		m_imgHeight = m_lpBmpInfoHead->biHeight;
		m_nBitCount = m_lpBmpInfoHead->biBitCount;
		lineByteOut = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;

		/*计算图像每行像素所占的字节数（必须是4的倍数）
		bmpWidth*biBitCount/8是实际占得字节数，加三，然后除以四，是为了得到大于等于它的最小整数，然后再乘以四就得到了最终要用的字节数
		例（bmpWidth*biBitCount/8==30，（30+3）/4=8,8*4=32,如果没有除四乘四，实际上用了三十个字节，可是必须是四的倍数）*/

		//计算颜色表长度
		m_nColorTableLength =
			ComputeColorTabalLength(m_lpBmpInfoHead->biBitCount);

		//如果有颜色表,则创建逻辑调色板

		if (m_nColorTableLength != 0){
			m_lpColorTable = (LPRGBQUAD)(m_lpDib + sizeof(BITMAPINFOHEADER));
			//MakePalette();
		}

		//m_pImgData指向DIB的位图数据起始位置
		m_pImgData = (LPBYTE)m_lpDib + sizeof(BITMAPINFOHEADER)+
			sizeof(RGBQUAD)* m_nColorTableLength;


	}
	catch (CException* pe)
	{
		AfxMessageBox("Read error");
		pe->Delete();
		return;
	}


}


void CPictureDlg::OnBnClickedBtnView()
{
	CDC*pDC = GetDC();
	CRect Video;
	GetDlgItem(IDC_STATIC_PICTURE)->GetWindowRect(Video);
	ScreenToClient(&Video);
	SetStretchBltMode(pDC->GetSafeHdc(), COLORONCOLOR);
	StretchDIBits(pDC->m_hDC, Video.left, Video.top, Video.Width(), Video.Height(), 0, 0,
		m_imgWidth, m_imgHeight, m_pImgData, (BITMAPINFO*)m_lpBmpInfoHead, DIB_RGB_COLORS, SRCCOPY);
}


void CPictureDlg::OnBnClickedBtnSave()
{
	//写模式打开文件
	CFile file;
	if (!file.Open("E:\\Code\\MyCode_cpp\\Halcon\\Picture\\al2.bmp", CFile::modeCreate | CFile::modeReadWrite
		))
		return;

	//填写文件头结构
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4d42;  // 'BM'
	bmfh.bfSize = 0;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+
		sizeof(RGBQUAD)* m_nColorTableLength;
	try {
		//文件头结构写进文件
		file.Write((LPVOID)&bmfh, sizeof(BITMAPFILEHEADER));

		//文件信息头结构写进文件
		file.Write(m_lpBmpInfoHead, sizeof(BITMAPINFOHEADER));

		//如果有颜色表的话，颜色表写进文件
		if (m_nColorTableLength != 0)
			file.Write(m_lpColorTable, sizeof(RGBQUAD)* m_nColorTableLength);

		//位图数据写进文件
		int imgBufSize = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4 * m_imgHeight;
		file.Write(m_pImgData, imgBufSize);
	}
	catch (CException* pe) {
		pe->Delete();
		AfxMessageBox("write error");
		return;
	}
}
