#pragma once

struct FILMITEM
{
	int filmid;
	int index;
	SQLString filmname;
	SQLString description;
	SQLString category;
	double price;
	int length;
	SQLString rate;
	SQLString actors;
};

class CFilmInfoUI : public CVerticalLayoutUI, public IListCallbackUI
{
public:
	CFilmInfoUI();
	~CFilmInfoUI();
	void Create();
	void UpdateRentInfoList();
	LPCTSTR GetItemText(CControlUI* pControl, int iIndex, int iSubItem);
private:
	CDialogBuilder m_dlgBuilder;
	vector<FILMITEM> filminfo;
};

