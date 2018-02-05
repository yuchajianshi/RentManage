#include "stdafx.h"
#include "main_frame.h"
#include "RentInfoUI.h"
#include "FilmInfoUI.h"
#include "ActorInfoUI.h"


MainFrame::~MainFrame()
{
	PostQuitMessage(0);
}

CDuiString MainFrame::GetSkinFolder()
{
	return  _T("skin\\FilmRent\\");
}

CDuiString MainFrame::GetSkinFile()
{
	return _T("filmrent.xml");
}

LPCTSTR MainFrame::GetWindowClassName() const
{
	return _T("FilmRent");
}

UINT MainFrame::GetClassStyle() const
{
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS;
}

UILIB_RESOURCETYPE MainFrame::GetResourceType() const
{
	return UILIB_ZIPRESOURCE;
}

LPCTSTR MainFrame::GetResourceID() const
{
	return MAKEINTRESOURCE(101);
}

void MainFrame::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void MainFrame::InitWindow()
{
	CRentInfoUI* pRentInfo = static_cast<CRentInfoUI*>(m_PaintManager.FindControl("rent_info"));
	pRentInfo->Create();
	CFilmInfoUI* pFilmInfo = static_cast<CFilmInfoUI*>(m_PaintManager.FindControl("film_info"));
	pFilmInfo->Create();
	CActorInfoUI* pActorInfo = static_cast<CActorInfoUI*>(m_PaintManager.FindControl("actor_info"));
	pActorInfo->Create();
}

void MainFrame::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		if (_tcsicmp(msg.pSender->GetName(), _T("btn_close")) == 0)
		{
			Close();
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("btn_min")) == 0)
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("btn_max")) == 0)
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			msg.pSender->SetVisible(false);
			CButtonUI *pButton = static_cast<CButtonUI *>(m_PaintManager.FindControl(_T("btn_restore")));
			pButton->SetVisible(true);
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("btn_restore")) == 0)
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
			msg.pSender->SetVisible(false);
			CButtonUI *pButton = static_cast<CButtonUI *>(m_PaintManager.FindControl(_T("btn_max")));
			pButton->SetVisible(true);
		}
	}
	else if (_tcsicmp(msg.sType, _T("selectchanged")) == 0)
	{
		CTabLayoutUI* pTabControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabs")));
		if (_tcsicmp(msg.pSender->GetName(), _T("opt_rentinfo")) == 0)
		{
			if (pTabControl && pTabControl->GetCurSel() != 0)
			{
				pTabControl->SelectItem(0);
			}
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("opt_filminfo")) == 0)
		{
			if (pTabControl && pTabControl->GetCurSel() != 1)
			{
				pTabControl->SelectItem(1);
			}
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("opt_actorinfo")) == 0)
		{
			if (pTabControl && pTabControl->GetCurSel() != 2)
			{
				pTabControl->SelectItem(2);
			}
		}
	}
}

CControlUI* MainFrame::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, _T("RentInfo")) == 0)
	{
		return new CRentInfoUI();
	}
	else if (_tcsicmp(pstrClass, _T("FilmInfo")) == 0)
	{
		return new CFilmInfoUI();
	}
	else if (_tcsicmp(pstrClass, _T("ActorInfo")) == 0)
	{
		return new CActorInfoUI();
	}

	return NULL;
}