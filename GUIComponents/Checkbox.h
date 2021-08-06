#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Checkbox : public Item {
	bool preCheck;
public:

	LPCWSTR GetText() { return GetTitle(); }
	void SetText(LPCWSTR str) { SetTitle(str); }

	bool GetCheck() {
		if (GetSelf() != nullptr)
			return SendMessage(GetSelf(), BM_GETCHECK, 0, 0);

		return preCheck;
	}
	void SetCheck(bool s) {
		if (GetSelf() != nullptr)
			SendMessage(GetSelf(), BM_SETCHECK, (WPARAM)s, 0);
		else
			preCheck = s;
	}
	
public:
	Checkbox() {
		SetClassname(L"BUTTON");
		SetStyle(WS_VISIBLE | WS_CHILD | BS_CHECKBOX);

		preCheck = false;		
	}
	virtual ~Checkbox() {}	
	
private:
	virtual bool BeforeCreate() override { return true; }
	virtual bool AfterCreate() override { return true; }	
};