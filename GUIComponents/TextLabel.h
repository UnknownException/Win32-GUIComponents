#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class TextLabel : public Item{
public:
	enum TextAlignment {
		ALIGNLEFT,
		ALIGNCENTER,
		ALIGNRIGHT
	};

private:
	bool sunken;
	TextAlignment textAlignment;

public:
	LPCWSTR GetText() { return GetTitle(); }
	void SetText(LPCWSTR t) { SetTitle(t); }

	bool GetSunken() { return sunken; }
	void SetSunken(bool b) { sunken = b; }

	TextAlignment GetTextAlignment() { return textAlignment; }
	void SetTextAlignment(TextAlignment ta) { textAlignment = ta; }

	TextLabel() {
		SetClassname(L"STATIC");
		SetStyle(WS_VISIBLE | WS_CHILD);

		sunken = false;
		textAlignment = ALIGNLEFT;
	}
	virtual ~TextLabel() {}	
	
private:
	virtual bool BeforeCreate() override {
		if(sunken)
			SetStyle(GetStyle() | SS_SUNKEN);

		if (textAlignment == ALIGNRIGHT)
			SetStyle(GetStyle() | SS_RIGHT);
		else if (textAlignment == ALIGNCENTER)
			SetStyle(GetStyle() | SS_CENTER);
		else
			SetStyle(GetStyle() | SS_LEFT);

		return true;
	}
	virtual bool AfterCreate() override {
		return true;
	}
};