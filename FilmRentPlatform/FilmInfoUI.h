#pragma once

class CFilmInfoUI : public CVerticalLayoutUI
{
public:
	CFilmInfoUI();
	~CFilmInfoUI();
	void Create();
private:
	CDialogBuilder m_dlgBuilder;
};

