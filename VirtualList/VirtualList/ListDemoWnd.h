#pragma once
using namespace DuiLib;

class CListDemoWnd : public WindowImplBase
{
public:
	CListDemoWnd();
	~CListDemoWnd();

protected:
	virtual void OnClick(TNotifyUI& msg);
//	virtual void Notify(TNotifyUI& msg);
// 	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void ShowRes();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);

private:
	virtual LPCTSTR    GetWindowClassName(void) const override;
	virtual CDuiString GetSkinFile()                  override;
	void InitAfterCreate();
private:
};