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

		OnClick = nullptr;
	}
	virtual ~Checkbox() {}	
	
	void (*OnClick)(bool);
private:
	virtual bool BeforeCreate(Item* parent) override { return true; }
	virtual bool AfterCreate() override { 
		SetCheck(_checked);

		return true;
	}

	virtual bool OnMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override {
		if (message != WM_COMMAND)
			return false;

		if (HIWORD(wParam) != BN_CLICKED)
			return false;

		HWND control = (HWND)lParam;
		if (control != GetSelf())
			return false;

		SetCheck(!GetCheck());

		if(OnClick)
			OnClick(GetCheck());

		return true;
	}
};