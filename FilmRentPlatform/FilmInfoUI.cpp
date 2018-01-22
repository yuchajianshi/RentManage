#include "Stdafx.h"
#include "FilmInfoUI.h"

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
}