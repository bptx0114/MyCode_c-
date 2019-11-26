#pragma once
#include "IVirtualDataProvider.h"

class CVirListBodyUI : public CListBodyUI
{
public:
	CVirListBodyUI(CListUI* pOwner);
	~CVirListBodyUI();

	void SetVerScrollRange(int nRange);

	void SetItemCount(int nCount);

	//ǿ���ػ�,�����ⲿ�ı�ĳЩ������
	void RedrawItems(int iItemFrom, int iItemTo);

	//void DoEvent(TEventUI& event);

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
	* @brief ˢ���б�
	* @return ��
	*/
	virtual void Refresh();

	/**
	* @brief ɾ����������
	* @return ��
	*/
	virtual void RemoveAll() override;

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
	* @brief �ÿؼ��ڿɼ���Χ��
	* @param[in] iIndex �ؼ�����
	* @param[in] bToTop �Ƿ������Ϸ�
	* @return ��
	*/
	void EnsureVisible(int iIndex, bool bToTop = false);

	/**
	* @brief ����λ��(�ӿؼ��Լ�����)
	* @param[in] rc ����ؼ�λ�� 
	* @param[in] bNeedInvalidate �Ƿ�ˢ��
	* @return ��
	*/
	virtual void SetPos(RECT rc, bool bNeedInvalidate = true);

	/// ��д����ӿڣ��ṩ���Ի�����
	/**
	* @brief �������ı�,���ù�����λ��,���Ƿ�ˢ�½���
	* @param[in] szPos ������λ��
	* @return ��
	*/
	virtual void SetScrollPos(SIZE szPos, bool bMsg = true);

	void EnsureVisible(int iIndex);

	/**
	* @brief ���²�������
	* @param[in] bForce �Ƿ�ǿ�����²���
	* @return ��
	*/
	void ReArrangeChild(bool bForce);
protected:

	/**
	* @brief ����ʵ����Ҫ�Ĺ�����λ��
	* @param[in] rc �ؼ�λ��
	* @return ��
	*/
	void SetPosInternally(RECT rc);

	/**
	* @brief ���һ������
	* @param[in] iIndex Ҫ�����λ��
	* @return ��
	*/
	void AddElement(int iIndex);//���������б����ûʲô��

	/**
	* @brief �Ƴ�һ������
	* @param[in] iIndex Ҫ�Ƴ�����������
	* @return ��
	*/
	void RemoveElement(int iIndex);

	/**
	* @brief ���̰���֪ͨ
	* @param[in] ch ����
	* @return ��
	*/
	virtual void OnKeyDown(TCHAR ch) {}

	/**
	* @brief ���̵���֪ͨ
	* @param[in] ch ����
	* @return ��
	*/
	virtual void OnKeyUp(TCHAR ch) {}

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

	/**
	* @brief ʹ��Ĭ�ϲ���
	* @return �ɹ����� true�����򷵻� false
	*/
	bool UseDefaultLayout();

	/**
	* @brief �õ�n��Ԫ�ض�Ӧ�ĸ߶Ⱥͣ�
	* @param[in] nCount Ҫ�õ�����Ԫ�صĸ߶ȣ�-1��ʾȫ��Ԫ��
	* @return ����ָ������Ԫ�صĸ߶Ⱥ�
	*/
	int CalcElementsHeight(int nCount);

	/**
	* @brief �õ��ɼ���Χ�ڵ�һ��Ԫ�ص�ǰһ��Ԫ������
	* @param[out] bottom ������һ��Ԫ�ص� bottom ֵ
	* @return ������һ��Ԫ�ص�����
	*/
	int GetTopElementIndex(int &bottom);

	/**
	* @brief �ж�ĳ��Ԫ���Ƿ��ڿɼ���Χ��
	* @param[in] iIndex Ԫ������
	* @return ���� true ��ʾ�ɼ�������Ϊ���ɼ�
	*/
	bool IsElementDisplay(int iIndex);

	/**
	* @brief �ж��Ƿ�Ҫ���²���
	* @param[out] direction ���Ϲ����������¹���
	* @return true Ϊ��Ҫ���²��֣�����Ϊ false
	*/
	bool NeedReArrange(ScrollDirection &direction);

	//δʹ��
	void Arrange();

public:
	/**
	* @brief ÿ������ˢ�¼���ʱ ���°���m_vSelIndex �е�������ʼ��
	* @param[in] rc λ��
	* @param[in] cxRequired ˮƽ��Ҫ�Ĺ����� Range 
	* @param[in] cyRequired ��ֱ��Ҫ�Ĺ�����Range
	* @return��
	*/
	void ProcessScrollBar(RECT rc, int cxRequired, int cyRequired);

	/**
	* @brief ÿ������ˢ�¼���ʱ ���°���m_vSelIndex �е�������ʼ��
	* @return��
	*/
	void InitSelectItem();


	/**
	* @brief ��ѡ
	* @param[in] iIndex ѡ������
	* @param[in] bTakeFocus �Ƿ��ȡ����
	* @return true �Ƿ�ѡ��
	*/
	bool SelectItem(int iIndex, bool bTakeFocus = false);

	/**
	* @brief ��ѡ
	* @param[in] iIndex ѡ������
	* @param[in] bTakeFocus �Ƿ��ȡ����
	* @return true �Ƿ�ѡ��
	*/
 	bool SelectMultiItem(int iIndex, bool bTakeFocus = false);

/// ����Ҫ��д begin
// 	bool SelectItemActivate(int iIndex);    // ˫��ѡ��
// 	void SetMultiSelect(bool bMultiSel); 
// 	bool IsMultiSelect() const;
//	bool UnSelectItem(int iIndex, bool bOthers = false);

/// ����Ҫ��д end
	/**
	* @brief ȫѡ
	* @return��
	*/
 	void SelectAllItems();

	/**
	* @brief �������ѡ��
	* @return ��
	*/
 	void UnSelectAllItems();
 	//֧�ַ�Χѡ�� add by ll  2019.04.02
	/**
	* @brief ��Χѡ��  m_iSelIndex ~ iIndex ����ѡ��
	* @param[in] iIndex ѡ�н�������
	* @param[in] bTakeFocus �Ƿ��ȡ����
	* @return true �Ƿ�ѡ��
	*/
 	virtual bool SelectRange(int iIndex, bool bTakeFocus = false);

	/**
	* @brief ��ȡѡ�е����� (ͨ��IVirtualDataProvider * ��ȡ����)
	* @return std::vector<int> ѡ������
	*/
	std::vector<int> GetSelectIndex();
private:
	bool m_bIsStartBoxSel = false;//�Ƿ�ʼ��ѡ

	int m_iStartBoxIndex = -1; //��ʼ��ѡ����
	int m_iEndBoxIndex = -1;//������ѡ����
	POINT m_BoxStartPt = { 0,0 };//��ѡ��ʼ���

					   //OwnerData
	IVirtualDataProvider*  m_pDataProvider;

	int m_nOwnerElementHeight = 0;	// ÿ����ĸ߶�	
	int m_nOwnerItemCount = 0;	// �б���ʵ�ؼ���������  
	int m_nOldYScrollPos = 0;
	bool m_bArrangedOnce = false;
	bool m_bForceArrange = false;	// ǿ�Ʋ��ֱ��

	int m_iCurlShowBeginIndex = 0;
	int m_iCurlShowEndIndex = 0;

	bool m_bScrollProcess = false;//��ֹSetPos �ظ�����, ������ѭ��

	int m_iSelIndex = -1;
	std::vector<int> m_vSelIndex;//ѡ������
};