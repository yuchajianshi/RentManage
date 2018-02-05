#pragma once

struct FILMNAME
{
	int filmid;
	SQLString filmname;
};

class CNewRentInfoUI : public WindowImplBase
{
public:
	CNewRentInfoUI();
	~CNewRentInfoUI();
	CDuiString GetSkinFolder();
	CDuiString GetSkinFile();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void OnRentOK();

protected:
	void Notify(TNotifyUI& msg);
	void OnFinalMessage(HWND hWnd);
	void InitWindow();

public:
	CDuiString filmname;
	CDuiString rentor;
	CDuiString renttime;
	CDuiString clerk;
	int returntype;
	vector<FILMNAME> allfilmname;
};

enum {
	RESULT_OK,
	RESULT_CANCEL
};