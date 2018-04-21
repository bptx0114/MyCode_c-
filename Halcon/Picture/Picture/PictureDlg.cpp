
// PictureDlg.cpp : ʵ���ļ�
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


// CPictureDlg �Ի���



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


// CPictureDlg ��Ϣ�������

BOOL CPictureDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPictureDlg::OnPaint()
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

		//��ȡBITMAPFILEHEADER�ṹ������bmfh��
		int nCount = file.Read((LPVOID)&bmfh, sizeof(BITMAPFILEHEADER));



		//Ϊm_lpDib����ռ䣬��ȡDIB���ڴ�

		m_lpDib = new BYTE[file.GetLength() - sizeof(BITMAPFILEHEADER)];

		file.Read(m_lpDib, file.GetLength() - sizeof(BITMAPFILEHEADER));

		//m_lpBmpInfoHeadλ��Ϊm_lpDib��ʼλ��
		m_lpBmpInfoHead = (LPBITMAPINFOHEADER)m_lpDib;

		//Ϊ��Ա������ֵ
		m_imgWidth = m_lpBmpInfoHead->biWidth;
		m_imgHeight = m_lpBmpInfoHead->biHeight;
		m_nBitCount = m_lpBmpInfoHead->biBitCount;
		lineByteOut = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;

		/*����ͼ��ÿ��������ռ���ֽ�����������4�ı�����
		bmpWidth*biBitCount/8��ʵ��ռ���ֽ�����������Ȼ������ģ���Ϊ�˵õ����ڵ���������С������Ȼ���ٳ����ľ͵õ�������Ҫ�õ��ֽ���
		����bmpWidth*biBitCount/8==30����30+3��/4=8,8*4=32,���û�г��ĳ��ģ�ʵ����������ʮ���ֽڣ����Ǳ������ĵı�����*/

		//������ɫ����
		m_nColorTableLength =
			ComputeColorTabalLength(m_lpBmpInfoHead->biBitCount);

		//�������ɫ��,�򴴽��߼���ɫ��

		if (m_nColorTableLength != 0){
			m_lpColorTable = (LPRGBQUAD)(m_lpDib + sizeof(BITMAPINFOHEADER));
			//MakePalette();
		}

		//m_pImgDataָ��DIB��λͼ������ʼλ��
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
	//дģʽ���ļ�
	CFile file;
	if (!file.Open("E:\\Code\\MyCode_cpp\\Halcon\\Picture\\al2.bmp", CFile::modeCreate | CFile::modeReadWrite
		))
		return;

	//��д�ļ�ͷ�ṹ
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4d42;  // 'BM'
	bmfh.bfSize = 0;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+
		sizeof(RGBQUAD)* m_nColorTableLength;
	try {
		//�ļ�ͷ�ṹд���ļ�
		file.Write((LPVOID)&bmfh, sizeof(BITMAPFILEHEADER));

		//�ļ���Ϣͷ�ṹд���ļ�
		file.Write(m_lpBmpInfoHead, sizeof(BITMAPINFOHEADER));

		//�������ɫ��Ļ�����ɫ��д���ļ�
		if (m_nColorTableLength != 0)
			file.Write(m_lpColorTable, sizeof(RGBQUAD)* m_nColorTableLength);

		//λͼ����д���ļ�
		int imgBufSize = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4 * m_imgHeight;
		file.Write(m_pImgData, imgBufSize);
	}
	catch (CException* pe) {
		pe->Delete();
		AfxMessageBox("write error");
		return;
	}
}
