#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Checkbox : public Item {
	bool _checked;
public:

	LPCWSTR GetText() { return GetTitle(); }
	void SetText(LPCWSTR str) { SetTitle(str); }

	bool GetCheck() {
		if (GetSelf() != nullptr)
			_checked = SendMessage(GetSelf(), BM_GETCHECK, 0, 0);

		return _checked;
	}
	void SetCheck(bool checked) {
		_checked = checked;
		
		if (GetSelf() != nullptr)
			SendMessage(GetSelf(), BM_SETCHECK, (WPARAM)_checked, 0);
	}
	
public:
	Checkbox() {
		SetClassname(L"BUTTON");
		SetStyle(WS_VISIBLE | WS_CHILD | BS_CHECKBOX);

		SetCheck(false);		
	}
	virtual ~Checkbox() {}	
	
private:
	virtual bool BeforeCreate() override { return true; }
	virtual bool AfterCreate() override { 
		SetCheck(_checked);

		return true;
	}	
};