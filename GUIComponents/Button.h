#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Button : public Item {
public:
	LPCWSTR GetText() { return GetTitle(); }
	void SetText(LPCWSTR str) { SetTitle(str); }

	Button() {
		SetClassname(L"BUTTON");
		SetStyle(WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON);
	}
	virtual ~Button();	
	
private:
	virtual bool BeforeCreate() override { return true; }
	virtual bool AfterCreate() override { return true; }
};