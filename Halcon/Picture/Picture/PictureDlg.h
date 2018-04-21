
// PictureDlg.h : 头文件
//

#pragma once


// CPictureDlg 对话框
class CPictureDlg : public CDialogEx
{
// 构造
public:
	CPictureDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PICTURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRead();
	afx_msg void OnBnClickedBtnView();
	afx_msg void OnBnClickedBtnSave();

	int 	ComputeColorTabalLength(int nBitCount);
	LPBYTE m_lpDib;
	//图像信息头指针
	LPBITMAPINFOHEADER m_lpBmpInfoHead;
	LPRGBQUAD m_lpColorTable;
	//图像的宽，像素为单位
	int m_imgWidth;

	//图像的高，像素为单位
	int m_imgHeight;
	int m_nBitCount;
	int lineByteOut;
	//颜色表长度（多少个表项）
	int m_nColorTableLength;
	BYTE* m_pImgData;




};
