#pragma once
#include <vector>

struct RENTITEM
{
	int rentid;
	int index;
	SQLString filmname;
	SQLString rentor;
	SQLString rentdate;
	SQLString backdate;
	SQLString clerk;
	CListTextElementUI *pListElement;
};

class CRentInfoUI : public CVerticalLayoutUI, public IListCallbackUI
{
public:
	CRentInfoUI();
	virtual ~CRentInfoUI();
	void Create();
	void UpdateRentInfoList();
	LPCTSTR GetItemText(CControlUI* pControl, int iIndex, int iSubItem);
	bool OnSearch(void *para);
	bool OnAddNewRent(void *para);

private:
	CDialogBuilder m_dlgBuilder;
	vector<RENTITEM> rentinfo;
};