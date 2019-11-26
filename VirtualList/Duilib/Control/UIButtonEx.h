#ifndef __UIBUTTON_EX_H__
#define __UIBUTTON_EX_H__

#pragma once

namespace DuiLib
{
	class UILIB_API CButtonExUI : public CButtonUI
	{
		DECLARE_DUICONTROL(CButtonExUI)

	public:
		CButtonExUI();

		LPCTSTR GetClass() const;
		LPVOID  GetInterface(LPCTSTR pstrName);
		void    PaintText(HDC hDC);
		void    DrawTextExBtn(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, DWORD dwTextColor, int iFont, UINT uStyle);
	};

}	// namespace DuiLib

#endif // __UIBUTTON_EX_H__