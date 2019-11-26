#pragma once
#include "IVirtualDataProvider.h"
#include "VirListBodyUI.h"
#include <list>



/*class CListUI;*/
class CVirtualListUI : public CListUI
{
public:
	CVirtualListUI();
	~CVirtualListUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	virtual void DoEvent(TEventUI& event);
	
	void SetItemCount(int nCount);

	/**
	* @brief �������ݴ������
	* @param[in] pProvider ��������Ҫ��д IVirtualDataProvider �Ľӿ�����Ϊ���ݴ������
	* @return ��
	*/
	virtual void SetDataProvider(IVirtualDataProvider * pDataProvider);

	virtual IVirtualDataProvider * GetDataProvider();

	/**
	* @brief ��������߶�
	* @param[in] nHeight �߶�ֵ
	* @return ��
	*/
	virtual void SetElementHeight(int nHeight);

	/**
	* @brief ��ʼ������
	* @param[in] nMaxItemCount ��ʼ��������Ĭ�� 50
	* @return ��
	*/
	virtual void InitElement(int nMaxItemCount = 50);

	/**
	* @brief ɾ����������
	* @return ��
	*/
	virtual void RemoveAll() override;

	bool Remove(CControlUI* pControl);
	bool RemoveAt(int iIndex);

	/**
	* @brief �����Ƿ�ǿ�����²���
	* @param[in] bForce ����Ϊ true Ϊǿ�ƣ�����Ϊ��ǿ��
	* @return ��
	*/
	void SetForceArrange(bool bForce);

	/**
	* @brief ��ȡ��ǰ���пɼ��ؼ�������
	* @param[out] collection �����б�
	* @return ��
	*/
	void GetDisplayCollection(std::vector<int>& collection);

	
	/**
	* @brief ��ȡѡ�е����� (ͨ��IVirtualDataProvider * ��ȡ����) 
	* @return std::vector<int> ѡ������
	*/
	std::vector<int> GetSelectIndex();
protected:
	/// ��д����ӿڣ��ṩ���Ի�����

	virtual void SetPos(RECT rc, bool bNeedInvalidate = true) ;

private:
	enum ScrollDirection
	{
		kScrollUp = -1,
		kScrollDown = 1
	};

	/**
	* @brief ����һ������
	* @return ���ش����������ָ��
	*/
	CControlUI* CreateElement();

	/**
	* @brief ���ָ������
	* @param[in] control ����ؼ�ָ��
	* @param[in] index ����
	* @return ���ش����������ָ��
	*/
	void FillElement(CControlUI *pControl, int iIndex);

	/**
	* @brief ��ȡԪ������
	* @return ����Ԫ����ָ��
	*/
	int GetElementCount();


private:

	void EnableScrollBar(bool bEnableVertical = true, bool bEnableHorizontal = false);


protected:
	bool SelectItem(int iIndex, bool bTakeFocus = false);
// 	bool SelectItemActivate(int iIndex);    // ˫��ѡ��
// 
 	bool SelectMultiItem(int iIndex, bool bTakeFocus = false);
// 	void SetMultiSelect(bool bMultiSel);
// 	bool IsMultiSelect() const;
// 	bool UnSelectItem(int iIndex, bool bOthers = false);
 	void SelectAllItems();
 	void UnSelectAllItems();
// 	//֧�ַ�Χѡ�� add by ll  2019.04.02
 	virtual bool SelectRange(int iIndex, bool bTakeFocus = false);

protected:
	bool m_bIsStartBoxSel = false;//�Ƿ�ʼ��ѡ

	int m_iStartBoxIndex = -1; //��ʼ��ѡ����
	int m_iEndBoxIndex = -1;//������ѡ����
	POINT m_BoxStartPt;//��ѡ��ʼ���


	IVirtualDataProvider*  m_pDataProvider ;//OwnerData

	CVirListBodyUI* m_pList;

	int m_nOwnerElementHeight;	// ÿ����ĸ߶�	
	int m_nOwnerItemCount;	// �б���ʵ�ؼ���������  
	int m_nOldYScrollPos;
	bool m_bArrangedOnce;
	bool m_bForceArrange;	// ǿ�Ʋ��ֱ��

	int m_iCurlShowBeginIndex = 0;
	int m_iCurlShowEndIndex = 0;

	bool m_bScrollProcess = false;//��ֹSetPos �ظ�����, ������ѭ��
};
