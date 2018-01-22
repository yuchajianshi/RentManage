#pragma once

class CActorInfoUI : public CVerticalLayoutUI
{
public:
	CActorInfoUI();
	~CActorInfoUI();
	void Create();
private:
	CDialogBuilder m_dlgBuilder;
};

