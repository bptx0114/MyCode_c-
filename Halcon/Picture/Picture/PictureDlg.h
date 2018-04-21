
// PictureDlg.h : ͷ�ļ�
//

#pragma once


// CPictureDlg �Ի���
class CPictureDlg : public CDialogEx
{
// ����
public:
	CPictureDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PICTURE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	//ͼ����Ϣͷָ��
	LPBITMAPINFOHEADER m_lpBmpInfoHead;
	LPRGBQUAD m_lpColorTable;
	//ͼ��Ŀ�����Ϊ��λ
	int m_imgWidth;

	//ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeight;
	int m_nBitCount;
	int lineByteOut;
	//��ɫ���ȣ����ٸ����
	int m_nColorTableLength;
	BYTE* m_pImgData;




};
