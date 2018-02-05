#include "Stdafx.h"
#include "RentInfoUI.h"
#include "NewRentInfoUI.h"
#include "GlobalClass.h"
#include <algorithm>

CRentInfoUI::CRentInfoUI()
{
}

CRentInfoUI::~CRentInfoUI()
{
}

void CRentInfoUI::Create()
{
	CVerticalLayoutUI* pRentInfoLayout = NULL;
	if (!m_dlgBuilder.GetMarkup()->IsValid()) {
		pRentInfoLayout = static_cast<CVerticalLayoutUI*>(m_dlgBuilder.Create(_T("rentinfo.xml"), (UINT)0, NULL, m_pManager, this));
		if (m_pManager != NULL) m_pManager->InitControls(pRentInfoLayout, this);
	}

	UpdateRentInfoList();

	CButtonUI *pSearchBtn = static_cast<CButtonUI *>(m_pManager->FindControl(_T("searchbtn")));
	if (pSearchBtn != nullptr)
	{
		pSearchBtn->OnNotify += MakeDelegate(this, &CRentInfoUI::OnSearch);
	}

	CButtonUI *pAddNewRent = static_cast<CButtonUI *>(m_pManager->FindControl(_T("addrentbtn")));
	if (pAddNewRent != nullptr)
	{
		pAddNewRent->OnNotify += MakeDelegate(this, &CRentInfoUI::OnAddNewRent);
	}

	CComboUI* pCombo = static_cast<CComboUI*>(m_pManager->FindControl(_T("searchcategory")));
	if (pCombo != nullptr)
	{
		CListLabelElementUI* pListElement;
		pListElement = new CListLabelElementUI;
		pListElement->SetText(_T("序号"));
		pCombo->Add(pListElement);
		pListElement = new CListLabelElementUI;
		pListElement->SetText(_T("电影名"));
		pCombo->Add(pListElement);
		pListElement = new CListLabelElementUI;
		pListElement->SetText(_T("租借人"));
		pCombo->Add(pListElement);
		pListElement = new CListLabelElementUI;
		pListElement->SetText(_T("租借日期"));
		pCombo->Add(pListElement);
		pListElement = new CListLabelElementUI;
		pListElement->SetText(_T("返还日期"));
		pCombo->Add(pListElement);
		pListElement = new CListLabelElementUI;
		pListElement->SetText(_T("负责员工"));
		pCombo->Add(pListElement);
		pCombo->SelectItem(0);
	}
}

void CRentInfoUI::UpdateRentInfoList()
{
	Statement *stmt = nullptr;
	ResultSet *res = nullptr;

	GlobalClass *pGlobalClass = GlobalClass::GetInstance();
	if (pGlobalClass->con != nullptr)
	{
		CListUI* pList = static_cast<CListUI*>(m_pManager->FindControl(_T("rentlist")));
		pList->SetTextCallback(this);
		int index = 0;
		try
		{
			stmt = pGlobalClass->con->createStatement();
			SQLString querystring;
			querystring = _T("SELECT rental_id,title film_name,CONCAT(c.first_name,' ',c.last_name) rentor,rental_date,return_date,CONCAT(f.first_name,' ',f.last_name) clerk ")
				_T("FROM rental r ")
				_T("INNER JOIN customer c ")
				_T("ON r.customer_id=c.customer_id ")
				_T("INNER JOIN inventory ")
				_T("ON r.inventory_id=inventory.inventory_id ")
				_T("INNER JOIN film ")
				_T("ON inventory.film_id=film.film_id ")
				_T("INNER JOIN staff f ")
				_T("ON r.staff_id=f.staff_id ORDER BY rental_id ");
			res = stmt->executeQuery(querystring);
			while (res->next())
			{
				CListTextElementUI *pListElement = new CListTextElementUI;
				RENTITEM ri;
				ri.index = ++index;
				ri.rentid = res->getInt(_T("rental_id"));
				ri.filmname = res->getString(_T("film_name"));
				ri.rentor = res->getString(_T("rentor"));
				ri.rentdate = res->getString(_T("rental_date"));
				ri.backdate = res->getString(_T("return_date"));
				ri.clerk = res->getString(_T("clerk"));
				ri.pListElement = pListElement;
				rentinfo.push_back(ri);
				pListElement->SetTag(ri.index);
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

LPCTSTR CRentInfoUI::GetItemText(CControlUI* pControl, int iIndex, int iSubItem)
{
	switch (iSubItem)
	{
	case 0:
	{
		TCHAR szIndex[10] = { 0 };
		_stprintf(szIndex, _T("%d"), rentinfo[iIndex].index);
		pControl->SetUserData(szIndex);  // 不用这两行语句的话在出了该函数之后szIndex的内容就被清空了
		return pControl->GetUserData();
		break;
	}
	case 1:
		return rentinfo[iIndex].filmname->c_str();
		break;
	case 2:
		return rentinfo[iIndex].rentor->c_str();
		break;
	case 3:
		return rentinfo[iIndex].rentdate->c_str();
		break;
	case 4:
		return rentinfo[iIndex].backdate->c_str();
		break;
	case 5:
		return rentinfo[iIndex].clerk->c_str();
		break;
	default:
		break;
	}
}

bool CRentInfoUI::OnSearch(void *para)
{
	TNotifyUI* pMsg = (TNotifyUI*)para;
	if (pMsg->sType == DUI_MSGTYPE_CLICK)
	{
		SQLString strTemp;
		CComboUI *pCombo = static_cast<CComboUI *>(m_pManager->FindControl(_T("searchcategory")));
		int sel = pCombo->GetCurSel();
		CEditUI *pEdit = static_cast<CEditUI *>(m_pManager->FindControl(_T("searchtext")));
		CListUI *pList = static_cast<CListUI *>(m_pManager->FindControl(_T("rentlist")));
		if (pEdit != nullptr && pList != nullptr)
		{
			if (pList->GetCount() > 0)
			{
				CListTextElementUI *pListItem = static_cast<CListTextElementUI *>(pList->GetItemAt(0));
				SIZE itemsize = pListItem->GetItemSize();
				CDuiString strSearchText = pEdit->GetText();
				switch (sel)
				{
				case 0:
				{
					int index;
					_stscanf_s(strSearchText, _T("%d"), &index);
					if (index <= 0 || index > pList->GetCount())
					{
						break;
					}

					for (int i = 0; i < rentinfo.size(); i++)
					{
						if (rentinfo[i].pListElement != nullptr)
						{
							rentinfo[i].pListElement->SetVisible(true);
						}
					}
					pList->SetScrollPos(CDuiSize(0, (index - 1) * itemsize.cy));
					break;
				}
				case 1:
				{
					for (int i = 0; i < rentinfo.size(); i++)
					{
						strTemp = rentinfo[i].filmname;
						transform(strTemp->begin(), strTemp->end(), strTemp->begin(), tolower);
						strSearchText.MakeLower();
						if (strTemp == strSearchText.GetData())
						{
							if (rentinfo[i].pListElement != nullptr)
							{
								rentinfo[i].pListElement->SetVisible(true);
							}
						}
						else
						{
							if (rentinfo[i].pListElement != nullptr)
							{
								rentinfo[i].pListElement->SetVisible(false);
							}
						}
					}
					break;
				}
				case 2:
				{     
					for (int i = 0; i < rentinfo.size(); i++)
					{
						if (rentinfo[i].pListElement != nullptr)
						{
							rentinfo[i].pListElement->SetVisible(true);
						}
					}
					for (int i = 0; i < rentinfo.size(); i++)
					{
						strTemp = rentinfo[i].rentor;
						transform(strTemp->begin(), strTemp->end(), strTemp->begin(), tolower);
						strSearchText.MakeLower();
						if (strTemp == strSearchText.GetData())
						{
							pList->SetScrollPos(CDuiSize(0, (rentinfo[i].index - 1) * itemsize.cy));
							break;
						}
					}
					break;
				}
				case 3:
				{
					for (int i = 0; i < rentinfo.size(); i++)
					{
						if (rentinfo[i].pListElement != nullptr)
						{
							rentinfo[i].pListElement->SetVisible(true);
						}
					}
					for (int i = 0; i < rentinfo.size(); i++)
					{
						if (rentinfo[i].rentdate == strSearchText.GetData())
						{
							pList->SetScrollPos(CDuiSize(0, (rentinfo[i].index - 1) * itemsize.cy));
							break;
						}
					}
					break;
				}
				case 4:
				{
					for (int i = 0; i < rentinfo.size(); i++)
					{
						if (rentinfo[i].pListElement != nullptr)
						{
							rentinfo[i].pListElement->SetVisible(true);
						}
					}
					for (int i = 0; i < rentinfo.size(); i++)
					{
						if (rentinfo[i].backdate == strSearchText.GetData())
						{
							pList->SetScrollPos(CDuiSize(0, (rentinfo[i].index - 1) * itemsize.cy));
							break;
						}
					}
					break;
				}
				case 5:
				{
					for (int i = 0; i < rentinfo.size(); i++)
					{
						strTemp = rentinfo[i].clerk;
						transform(strTemp->begin(), strTemp->end(), strTemp->begin(), tolower);
						strSearchText.MakeLower();
						if (strTemp == strSearchText.GetData())
						{
							if (rentinfo[i].pListElement != nullptr)
							{
								rentinfo[i].pListElement->SetVisible(true);
							}
						}
						else
						{
							if (rentinfo[i].pListElement != nullptr)
							{
								rentinfo[i].pListElement->SetVisible(false);
							}
						}
					}
					break;
				}
				default:
					break;
				}
			}
		}
		return true;
	}
	return false;
}

bool CRentInfoUI::OnAddNewRent(void *para)
{
	TNotifyUI* pMsg = (TNotifyUI*)para;
	if (pMsg->sType == DUI_MSGTYPE_CLICK)
	{
		CNewRentInfoUI *pNewRent = new CNewRentInfoUI();
		pNewRent->Create(m_pManager->GetPaintWindow(), _T(""), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
		pNewRent->CenterWindow();
		pNewRent->ShowModal();
		if (pNewRent->returntype == RESULT_OK)
		{
			Statement *stmt = nullptr;
			ResultSet *res = nullptr;
			try
			{
				GlobalClass *pGlobalClass = GlobalClass::GetInstance();
				if (pGlobalClass->con != nullptr)
				{
					stmt = pGlobalClass->con->createStatement();
					CDuiString strTemp;
					SQLString querystring;

					stmt->execute(_T("START TRANSACTION"));

					querystring = _T("SELECT film_id FROM film WHERE title = '");
					querystring += (LPCTSTR)pNewRent->filmname;
					querystring += _T("'");
					res = stmt->executeQuery(querystring);
					int filmid;
					if (res->next())
					{
						filmid = res->getInt(_T("film_id"));
						delete res;
					}
					else
					{
						goto destroy;
					}

					querystring = _T("SELECT store_id FROM store LIMIT 1");
					res = stmt->executeQuery(querystring);
					int storeid;
					if (res->next())
					{
						storeid = res->getInt(_T("store_id"));
						delete res;
					}
					else
					{
						goto destroy;
					}

					querystring = _T("INSERT INTO inventory(film_id, store_id) VALUES");
					strTemp.Format(_T("(%d, %d)"), filmid, storeid);
					querystring += (LPCTSTR)strTemp;
					stmt->execute(querystring);

					querystring = _T("SELECT inventory_id FROM inventory ORDER BY inventory_id DESC LIMIT 1");
					res = stmt->executeQuery(querystring);
					int inventoryid;
					if (res->next())
					{
						inventoryid = res->getInt(_T("inventory_id"));
   						delete res;
					}
					else
					{
						stmt->execute(_T("ROLLBACK"));
						goto destroy;
					}

					querystring = _T("SELECT customer_id FROM customer WHERE STRCMP(CONCAT(first_name,' ',last_name), '");
					querystring += (LPCTSTR)pNewRent->rentor;
					querystring += _T("') = 0");
					res = stmt->executeQuery(querystring);
					int customerid;
					if (res->next())
					{
						customerid = res->getInt(_T("customer_id"));
						delete res;
					}
					else
					{
						stmt->execute(_T("ROLLBACK"));
						goto destroy;
					}

					querystring = _T("SELECT staff_id FROM staff WHERE STRCMP(CONCAT(first_name,' ',last_name), '");
					querystring += (LPCTSTR)pNewRent->clerk;
					querystring += _T("') = 0");
					res = stmt->executeQuery(querystring);
					int staffid;
					if (res->next())
					{
						staffid = res->getInt(_T("staff_id"));
					}
					else
					{
						stmt->execute(_T("ROLLBACK"));
						goto destroy;
					}

					int time;
					_stscanf_s(pNewRent->renttime, _T("%d"), &time);
					strTemp.Format(_T("INSERT INTO rental(rental_date, inventory_id, customer_id, return_date, staff_id) ")
						_T("VALUES(NOW(), %d, %d, DATE_ADD(NOW(),INTERVAL %d DAY), %d)"), inventoryid, customerid, time, staffid);
					stmt->execute((LPCTSTR)strTemp);

					stmt->execute(_T("COMMIT"));

				destroy:delete stmt;
					delete res;
				}
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
		delete pNewRent;   // 由于在DoModal之后还需要使用NewRentInfo类中的信息，因此该类的销毁不在FinalMessage里面完成，在这里完成
		return true;
	}
	return false;
}