#include "Stdafx.h"
#include "ActorInfoUI.h"

CActorInfoUI::CActorInfoUI()
{
}

CActorInfoUI::~CActorInfoUI()
{
}

void CActorInfoUI::Create()
{
	CVerticalLayoutUI* pActorInfoLayout = NULL;
	if (!m_dlgBuilder.GetMarkup()->IsValid()) {
		pActorInfoLayout = static_cast<CVerticalLayoutUI*>(m_dlgBuilder.Create(_T("actorinfo.xml"), (UINT)0, NULL, m_pManager, this));
		if (m_pManager != NULL) m_pManager->InitControls(pActorInfoLayout, this);
	}
}