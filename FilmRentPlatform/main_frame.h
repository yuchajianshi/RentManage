#pragma once

class MainFrame : public WindowImplBase
{
public:
	~MainFrame();
	CDuiString GetSkinFolder();
	CDuiString GetSkinFile();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	CControlUI* CreateControl(LPCTSTR pstrClass);

protected:
	void Notify(TNotifyUI& msg);
	void OnFinalMessage(HWND hWnd);
	void InitWindow();
};