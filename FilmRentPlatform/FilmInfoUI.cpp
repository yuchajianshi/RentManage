#include "Stdafx.h"
#include "FilmInfoUI.h"
#include "GlobalClass.h"

CFilmInfoUI::CFilmInfoUI()
{
}

CFilmInfoUI::~CFilmInfoUI()
{
}

void CFilmInfoUI::Create()
{
	CVerticalLayoutUI* pFilmInfoLayout = NULL;
	if (!m_dlgBuilder.GetMarkup()->IsValid()) {
		pFilmInfoLayout = static_cast<CVerticalLayoutUI*>(m_dlgBuilder.Create(_T("filminfo.xml"), (UINT)0, NULL, m_pManager, this));
		if (m_pManager != NULL) m_pManager->InitControls(pFilmInfoLayout, this);
	}

	UpdateRentInfoList();
}

void CFilmInfoUI::UpdateRentInfoList()
{
	Statement *stmt = nullptr;
	ResultSet *res = nullptr;

	GlobalClass *pGlobalClass = GlobalClass::GetInstance();
	if (pGlobalClass->con != nullptr)
	{
		CListUI* pList = static_cast<CListUI*>(m_pManager->FindControl(_T("filmlist")));
		pList->SetTextCallback(this);
		int index = 0;
		try
		{
			stmt = pGlobalClass->con->createStatement();
			SQLString querystring;
			querystring = _T("SELECT FID film_id, title film_name, description, category, price, length, length, rating, actors FROM film_list");
			res = stmt->executeQuery(querystring);
			while (res->next())
			{
				CListTextElementUI *pListElement = new CListTextElementUI;
				FILMITEM fi;
				fi.index = ++index;
				fi.filmid = res->getInt(_T("film_id"));
				fi.filmname = res->getString(_T("film_name"));
				fi.description = res->getString(_T("description"));
				fi.category = res->getString(_T("category"));
				fi.price = res->getDouble(_T("price"));
				fi.length = res->getInt(_T("length"));
				fi.rate = res->getString(_T("rating"));
				fi.actors = res->getString(_T("actors"));
				filminfo.push_back(fi);
				pList->Add(pListElement);
			}
			delete res;
			delete stmt;
		}
		catch (SQLException &e)
		{
			if (stmt != nullptr)
			{
				delete stmt;
			}
			if (res != nullptr)
			{
				delete res;
			}
			::MessageBox(NULL, e.what(), _T("提示"), MB_OK);
		}
	}
}

LPCTSTR CFilmInfoUI::GetItemText(CControlUI* pControl, int iIndex, int iSubItem)
{
	switch (iSubItem)
	{
	case 0:
	{
		TCHAR szIndex[10] = { 0 };
		_stprintf(szIndex, _T("%d"), filminfo[iIndex].index);
		pControl->SetUserData(szIndex);  // 不用这两行语句的话在出了该函数之后szIndex的内容就被清空了
		return pControl->GetUserData();
	}
	case 1:
		return filminfo[iIndex].filmname->c_str();
	case 2:
		return filminfo[iIndex].description->c_str();
	case 3:
		return filminfo[iIndex].category->c_str();
	case 4:
	{
		TCHAR szPrice[20] = { 0 };
		_stprintf(szPrice, _T("%g"), filminfo[iIndex].price);
		pControl->SetUserData(szPrice);
		return pControl->GetUserData();
	}
	case 5:
	{
		TCHAR szLength[10] = { 0 };
		_stprintf(szLength, _T("%d"), filminfo[iIndex].length);
		pControl->SetUserData(szLength);
		return pControl->GetUserData();
	}
	case 6:
		return filminfo[iIndex].rate->c_str();
	case 7:
		return filminfo[iIndex].actors->c_str();
	default:
		break;
	}
}