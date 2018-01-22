#include "stdafx.h"
#include "main_frame.h"


MainFrame::~MainFrame()
{
	PostQuitMessage(0);
}

CDuiString MainFrame::GetSkinFolder()
{
	return  _T("skin\\TestDuilib\\");
}

CDuiString MainFrame::GetSkinFile()
{
	return _T("test.xml");
}

LPCTSTR MainFrame::GetWindowClassName() const
{
	return _T("MyTest");
}

UINT MainFrame::GetClassStyle() const
{ 
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; 
}

void MainFrame::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void MainFrame::InitWindow()
{
	/*TCHAR szBuf[20] = { 0 };
	CComboUI* pControl = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("testcombo")));
	for (int i = 0; i < 10; i++)
	{
		_stprintf(szBuf, _T("这是测试%d"), i + 1);
		CListLabelElementUI* pListElement = new CListLabelElementUI;
		pListElement->SetText(szBuf);
		pControl->Add(pListElement);
	}
	pControl->SelectItem(2);*/
}

void MainFrame::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		/*if (_tcsicmp(msg.pSender->GetName(), _T("closebtn")) == 0)
		{
			Close();
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("minbtn")) == 0)
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("maxbtn")) == 0)
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("restorebtn")) == 0)
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
		}
		else if (_tcsicmp(msg.pSender->GetName(), _T("testbtn")) == 0)
		{
			CComboUI* pControl = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("testcombo")));
			CDuiString str = pControl->GetText();
			MessageBox(NULL, str, _T("提示"), MB_OK);
		}*/
	}
}