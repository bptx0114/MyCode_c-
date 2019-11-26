#pragma once
#include "IVirtualDataProvider.h"

using namespace DuiLib;


class MVirtualDataProvider : public IVirtualDataProvider, public IDialogBuilderCallback
{
public:
	MVirtualDataProvider(CPaintManagerUI* pPaint);



	virtual DuiLib::CControlUI* CreateControl(LPCTSTR pstrClass);


	/**
	* @brief ����һ������
	* @return ���ش����������ָ��
	*/
	virtual CControlUI* CreateElement();
	

	/**
	* @brief ���ָ������
	* @param[in] control ����ؼ�ָ��
	* @param[in] index ����
	* @return ���ش����������ָ��
	*/
	virtual void FillElement(CControlUI *pControl, int index);
	

	/**
	* @brief ��ȡ��������
	* @return ������������
	*/
	virtual int GetElementtCount();
	
protected:
	CPaintManagerUI* m_pManager;
	CDialogBuilder m_dlgBuilder;
};