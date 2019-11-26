#include "StdAfx.h"
#include "UIButtonEx.h"

namespace DuiLib
{
	IMPLEMENT_DUICONTROL(CButtonExUI)

	CButtonExUI::CButtonExUI()
	{

	}

	LPCTSTR CButtonExUI::GetClass() const
	{
		return _T("ButtonExUI");
	}

	LPVOID CButtonExUI::GetInterface(LPCTSTR pstrName)
	{
		if (_tcsicmp(pstrName, DUI_CTR_BUTTONEX) == 0) return static_cast<CButtonExUI*>(this);
		return nullptr;
	}

	void CButtonExUI::PaintText(HDC hDC)
	{
		if (IsFocused()) m_uButtonState |= UISTATE_FOCUSED;
		else m_uButtonState &= ~UISTATE_FOCUSED;
		if (!IsEnabled()) m_uButtonState |= UISTATE_DISABLED;
		else m_uButtonState &= ~UISTATE_DISABLED;

		if (m_dwTextColor == 0) m_dwTextColor = m_pManager->GetDefaultFontColor();
		if (m_dwDisabledTextColor == 0) m_dwDisabledTextColor = m_pManager->GetDefaultDisabledColor();

		CDuiString sText = GetText();
		if (sText.IsEmpty()) return;

		RECT m_rcTextPadding = CButtonExUI::m_rcTextPadding;
		GetManager()->GetDPIObj()->Scale(&m_rcTextPadding);
		int nLinks = 0;
		RECT rc = m_rcItem;
		rc.left += m_rcTextPadding.left;
		rc.right -= m_rcTextPadding.right;
		rc.top += m_rcTextPadding.top;
		rc.bottom -= m_rcTextPadding.bottom;

		DWORD clrColor = IsEnabled() ? m_dwTextColor : m_dwDisabledTextColor;

		if (((m_uButtonState & UISTATE_PUSHED) != 0) && (GetPushedTextColor() != 0))
			clrColor = GetPushedTextColor();
		else if (((m_uButtonState & UISTATE_HOT) != 0) && (GetHotTextColor() != 0))
			clrColor = GetHotTextColor();
		else if (((m_uButtonState & UISTATE_FOCUSED) != 0) && (GetFocusedTextColor() != 0))
			clrColor = GetFocusedTextColor();
		else if (((m_uButtonState & UISTATE_HOT) != 0))
			sText = GetHotText();
		if (m_bShowHtml)
			CRenderEngine::DrawHtmlText(hDC, m_pManager, rc, sText, clrColor, \
			NULL, NULL, nLinks, m_uTextStyle);
		else
			DrawTextExBtn(hDC, m_pManager, rc, sText, clrColor, \
			m_iFont, m_uTextStyle);
	}

	void CButtonExUI::DrawTextExBtn(HDC hDC, CPaintManagerUI* pManager, RECT& rc, LPCTSTR pstrText, DWORD dwTextColor, int iFont, UINT uStyle)
	{
		HDC hPaintDC = ::CreateCompatibleDC(hDC);
		HBITMAP hPaintBitmap = ::CreateCompatibleBitmap(hDC, (rc.right - rc.left), (rc.bottom - rc.top));
		HBITMAP hOldPaintBitmap = (HBITMAP) ::SelectObject(hPaintDC, hPaintBitmap);

		::BitBlt(hPaintDC, 0, 0, (rc.right - rc.left), (rc.bottom - rc.top), hDC, rc.left, rc.top, SRCCOPY);

		ASSERT(::GetObjectType(hPaintDC) == OBJ_DC || ::GetObjectType(hPaintDC) == OBJ_MEMDC);
		if (pstrText == NULL || pManager == NULL) return;

		if (pManager->IsLayered() || pManager->IsUseGdiplusText())
		{
			HFONT hOldFont = (HFONT)::SelectObject(hPaintDC, pManager->GetFont(iFont));
			Gdiplus::Graphics graphics(hPaintDC);
			Gdiplus::Font font(hPaintDC, pManager->GetFont(iFont));
			Gdiplus::TextRenderingHint trh = Gdiplus::TextRenderingHintAntiAliasGridFit;
			
			graphics.SetTextRenderingHint(trh);
			graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);
			graphics.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
			graphics.TranslateTransform((Gdiplus::REAL)0, (Gdiplus::REAL)0);
			graphics.RotateTransform(45.0F, Gdiplus::MatrixOrderAppend);
			Gdiplus::RectF rectF((Gdiplus::REAL)20, (Gdiplus::REAL)-55, (Gdiplus::REAL)(rc.right - rc.left), (Gdiplus::REAL)(rc.bottom - rc.top));
			Gdiplus::SolidBrush brush(Gdiplus::Color(254, GetBValue(dwTextColor), GetGValue(dwTextColor), GetRValue(dwTextColor)));

			Gdiplus::StringFormat stringFormat = Gdiplus::StringFormat::GenericTypographic();

			if ((uStyle & DT_END_ELLIPSIS) != 0) {
				stringFormat.SetTrimming(Gdiplus::StringTrimmingEllipsisCharacter);
			}

			int formatFlags = 0;
			if ((uStyle & DT_NOCLIP) != 0) {
				formatFlags |= Gdiplus::StringFormatFlagsNoClip;
			}
			if ((uStyle & DT_SINGLELINE) != 0) {
				formatFlags |= Gdiplus::StringFormatFlagsNoWrap;
			}

			stringFormat.SetFormatFlags(formatFlags);

			if ((uStyle & DT_LEFT) != 0) {
				stringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
			}
			else if ((uStyle & DT_CENTER) != 0) {
				stringFormat.SetAlignment(Gdiplus::StringAlignmentCenter);
			}
			else if ((uStyle & DT_RIGHT) != 0) {
				stringFormat.SetAlignment(Gdiplus::StringAlignmentFar);
			}
			else {
				stringFormat.SetAlignment(Gdiplus::StringAlignmentNear);
			}
			stringFormat.GenericTypographic();
			if ((uStyle & DT_TOP) != 0) {
				stringFormat.SetLineAlignment(Gdiplus::StringAlignmentNear);
			}
			else if ((uStyle & DT_VCENTER) != 0) {
				stringFormat.SetLineAlignment(Gdiplus::StringAlignmentCenter);
			}
			else if ((uStyle & DT_BOTTOM) != 0) {
				stringFormat.SetLineAlignment(Gdiplus::StringAlignmentFar);
			}
			else {
				stringFormat.SetLineAlignment(Gdiplus::StringAlignmentNear);
			}
#ifdef UNICODE
			if ((uStyle & DT_CALCRECT) != 0)
			{
				Gdiplus::RectF bounds;

				graphics.MeasureString(pstrText, -1, &font, rectF, &stringFormat, &bounds);

				// MeasureString存在计算误差，这里加一像素
				rc.bottom = rc.top + (long)bounds.Height + 1;
				rc.right = rc.left + (long)bounds.Width + 1;
			}
			else
			{
				graphics.DrawString(pstrText, -1, &font, rectF, &stringFormat, &brush);
			}
#else
			DWORD dwSize = MultiByteToWideChar(CP_ACP, 0, pstrText, -1, NULL, 0);
			WCHAR * pcwszDest = new WCHAR[dwSize + 1];
			memset(pcwszDest, 0, (dwSize + 1) * sizeof(WCHAR));
			MultiByteToWideChar(CP_ACP, NULL, pstrText, -1, pcwszDest, dwSize);
			if (pcwszDest != NULL)
			{
				if ((uStyle & DT_CALCRECT) != 0)
				{
					Gdiplus::RectF bounds;
					graphics.MeasureString(pcwszDest, -1, &font, rectF, &stringFormat, &bounds);
					rc.bottom = rc.top + (long)(bounds.Height * 1.06);
					rc.right = rc.left + (long)(bounds.Width * 1.06);
				}
				else
				{
					graphics.DrawString(pcwszDest, -1, &font, rectF, &stringFormat, &brush);
				}
				delete[]pcwszDest;
			}
#endif
			::SelectObject(hPaintDC, hOldFont);
		}
		else
		{
			::SetBkMode(hPaintDC, TRANSPARENT);
			::SetTextColor(hPaintDC, RGB(GetBValue(dwTextColor), GetGValue(dwTextColor), GetRValue(dwTextColor)));
			HFONT hOldFont = (HFONT)::SelectObject(hPaintDC, pManager->GetFont(iFont));
			int fonticonpos = CDuiString(pstrText).Find(_T("&#x"));
			if (fonticonpos != -1) {
				CDuiString strUnicode = CDuiString(pstrText).Mid(fonticonpos + 3);
				if (strUnicode.GetLength() > 4) strUnicode = strUnicode.Mid(0, 4);
				if (strUnicode.Right(1).CompareNoCase(_T(" ")) == 0) {
					strUnicode = strUnicode.Mid(0, strUnicode.GetLength() - 1);
				}
				if (strUnicode.Right(1).CompareNoCase(_T(";")) == 0) {
					strUnicode = strUnicode.Mid(0, strUnicode.GetLength() - 1);
				}
				wchar_t wch[2] = { 0 };
				wch[0] = static_cast<wchar_t>(_tcstol(strUnicode.GetData(), 0, 16));
				::DrawTextW(hPaintDC, wch, -1, &rc, uStyle);
			}
			else {
				::DrawText(hPaintDC, pstrText, -1, &rc, uStyle);
			}
			::SelectObject(hPaintDC, hOldFont);
		}

		::BitBlt(hDC, rc.left, rc.top, (rc.right - rc.left), (rc.bottom - rc.top), hPaintDC, 0, 0, SRCCOPY);

		::DeleteObject(hPaintBitmap);
		::DeleteDC(hPaintDC);
	}

}