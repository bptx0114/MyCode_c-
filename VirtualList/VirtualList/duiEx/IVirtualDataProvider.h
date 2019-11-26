#pragma once



//////////////////////////////////////////////////////////////////////////
// �����б������ṩ��,�������,��ʵ��ʹ�ó�����������,ʵ�ֶ�Ӧ�Ľӿڹ���
//////////////////////////////////////////////////////////////////////////

/**
* @brief �����б�ӿ���
* �ṩ�����߶��������ݹ�����Ի�����
*/
class IVirtualDataProvider
{
public:
	/**
	* @brief ����һ������
	* @return ���ش����������ָ��
	*/
	virtual CControlUI* CreateElement() abstract;

	/**
	* @brief ���ָ������
	* @param[in] control ����ؼ�ָ��
	* @param[in] index ����
	* @return ���ش����������ָ��
	*/
	virtual void FillElement(CControlUI *pControl, int index) abstract;

	/**
	* @brief ��ȡ��������
	* @return ������������
	*/
	virtual int GetElementtCount() abstract;
};