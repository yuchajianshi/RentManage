#include "stdafx.h"
#include "NewRentInfoUI.h"
#include "GlobalClass.h"

CNewRentInfoUI::CNewRentInfoUI()
{
}

CNewRentInfoUI::~CNewRentInfoUI()
{
}

CDuiString CNewRentInfoUI::GetSkinFolder()
{
	return  _T("skin\\FilmRent\\");
}

CDuiString CNewRentInfoUI::GetSkinFile()
{
	return _T("newrent.xml");
}

LPCTSTR CNewRentInfoUI::GetWindowClassName() const
{
	return _T("NewRentInfo");
}

UINT CNewRentInfoUI::GetClassStyle() const
{
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS;
}

void CNewRentInfoUI::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
}

void CNewRentInfoUI::InitWindow()
{
	Statement *stmt = nullptr;
	ResultSet *res = nullptr;

	GlobalClass *pGlobalClass = GlobalClass::GetInstance();
	if (pGlobalClass->con != nullptr)
	{
		CComboUI *pComboFileName = static_cast<CComboUI *>(m_PaintManager.FindControl(_T("film_name")));
		CComboUI *pComboRentor = static_cast<CComboUI *>(m_PaintManager.FindControl(_T("rentor")));
		try
		{
			stmt = pGlobalClass->con->createStatement();
			SQLString querystring;
			querystring = _T("SELECT film_id,title FROM film");
			res = stmt->executeQuery(querystring);
			while (res->next())
			{
				FILMNAME fn;
				fn.filmid = res->getInt(_T("film_id"));
				fn.filmname = res->getString(_T("title"));
				allfilmname.push_back(fn);
				CListLabelElementUI *pComboElement = new CListLabelElementUI;
				pComboElement->SetText(fn.filmname.c_str());
				pComboFileName->Add(pComboElement);
			}
			if (pComboFileName->GetCount() > 0)
			{
				pComboFileName->SelectItem(0);
			}
			delete res;
			
			querystring = _T("SELECT CONCAT(first_name,' ',last_name) rentor from customer");
			res = stmt->executeQuery(querystring);
			while (res->next())
			{
				SQLString customer_name = res->getString(_T("rentor"));
				CListLabelElementUI *pComboElement = new CListLabelElementUI;
				pComboElement->SetText(customer_name->c_str());
				pComboRentor->Add(pComboElement);
			}
			if (pComboRentor->GetCount() > 0)
			{
				pComboRentor->SelectItem(0);
			}

			delete stmt;
			delete res;
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

void CNewRentInfoUI::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		if (_tcsicmp(msg.pSender->GetName(), _T("btn_close")) == 0)
		{
			returntype = RESULT_CANCEL;
			Close();
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("rent_ok")) == 0)
		{
			returntype = RESULT_OK;
			OnRentOK();
		}
	}
}

void CNewRentInfoUI::OnRentOK()
{
	CComboUI *pFilmName = static_cast<CComboUI *>(m_PaintManager.FindControl(_T("film_name")));
	if (pFilmName != nullptr)
	{
		filmname = pFilmName->GetText();
		if (filmname.IsEmpty())
		{
			::MessageBox(NULL, _T("电影名不能为空"), _T("提示"), MB_OK);
			return;
		}
	}

	CComboUI *pRentor = static_cast<CComboUI *>(m_PaintManager.FindControl(_T("rentor")));
	if (pRentor != nullptr)
	{
		rentor = pRentor->GetText();
		if (rentor.IsEmpty())
		{
			::MessageBox(NULL, _T("租借人不能为空"), _T("提示"), MB_OK);
			return;
		}
	}

	CEditUI *pRentTime = static_cast<CEditUI *>(m_PaintManager.FindControl(_T("rent_time")));
	if (pRentTime != nullptr)
	{
		renttime = pRentTime->GetText();
		if (renttime.IsEmpty())
		{
			::MessageBox(NULL, _T("租借时长不能为空"), _T("提示"), MB_OK);
			return;
		}
	}

	CEditUI *pClerk = static_cast<CEditUI *>(m_PaintManager.FindControl(_T("clerk")));
	if (pClerk != nullptr)
	{
		clerk = pClerk->GetText();
		if (clerk.IsEmpty())
		{
			::MessageBox(NULL, _T("负责人不能为空"), _T("提示"), MB_OK);
			return;
		}
	}
	Close();
}