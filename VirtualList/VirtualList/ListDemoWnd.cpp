#include "stdafx.h"
#include "ListDemoWnd.h"
#include "duiEx/VirtualListUI.h"
#include "duiEx/ListDataProvider.h"


CListDemoWnd::CListDemoWnd()
{

}

CListDemoWnd::~CListDemoWnd()
{

}

void CListDemoWnd::OnClick(TNotifyUI& msg)
{
	if (msg.pSender->GetName() == L"btnSearch")
	{
		ShowRes();
// 		CVirTileLayoutUI*  pTileLayout = static_cast<CVirTileLayoutUI*>(m_pm.FindControl(L"VirTileDemo"));
// 		MVirtualDataProvider* pDataProvider = new MVirtualDataProvider(&m_pm);
// 		pTileLayout->SetDataProvider(pDataProvider);
// 		pTileLayout->SetElementHeight(50);
// 		pTileLayout->InitElement(100);
	}
	return __super::OnClick(msg);
}

void CListDemoWnd::ShowRes()
{
	CVirtualListUI* pList = static_cast<CVirtualListUI*>(m_pm.FindControl(L"ListDemo"));
	if (NULL != pList)
	{
		pList->RemoveAll();

		MVirtualDataProvider* pFileListProvider = new MVirtualDataProvider(&m_pm);
		

		//初始化之前需要清空列表和数据

		pList->SetDataProvider(pFileListProvider);
		pList->SetElementHeight(22);
		
		pList->InitElement();
		
	}
}

DuiLib::CControlUI* CListDemoWnd::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, L"VirList") == 0)
	{
		return new CVirtualListUI();
	}
	return NULL;
}

LPCTSTR CListDemoWnd::GetWindowClassName(void) const
{
	return L"CVirtualListDemoWnd";
}

DuiLib::CDuiString CListDemoWnd::GetSkinFile()
{
	return L"VirtualListWnd.xml";
}

void CListDemoWnd::InitAfterCreate()
{

}

