#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class TextBox : public Item {
public:
	enum TextAlignment {
		ALIGNLEFT,
		ALIGNCENTER,
		ALIGNRIGHT
	};

private:
	bool multiLine;
	bool verticalScroll;
	bool readOnly;
	LPWSTR text;
	TextAlignment textAlignment;

	void ClearText() {
		if (text) {
			delete[] text;
			text = nullptr;
		}
	}

public:
	LPCWSTR GetText() {
		if (GetSelf()) {
			ClearText();

			int length = static_cast<int>(SendMessage(GetSelf(), WM_GETTEXTLENGTH, 0, 0)) + 1;
			text = new WCHAR[length];
			SendMessage(GetSelf(), WM_GETTEXT, length, (LPARAM)text);
		}

		return text;
	}
	void SetText(LPCWSTR string) {
		if (GetSelf()) {
			SendMessage(GetSelf(), WM_SETTEXT, 0, (LPARAM)string);
		} 
		else {
			ClearText();

			text = new WCHAR[wcslen(string) + 1];
			wcscpy_s(text, wcslen(string) + 1, string);
		}
	}
	void AppendText(LPCWSTR string) {
		LPCWSTR currentText = GetText();

		size_t appendedLength = wcslen(currentText) + wcslen(string) + 1;
		WCHAR* appended = new WCHAR[appendedLength];
		wcscpy_s(appended, appendedLength, currentText);
		wcscat_s(appended, appendedLength, (WCHAR*)string);
		appended[appendedLength - 1] = 0;

		SetText(appended);
		delete[] appended;
	}

	bool GetMultiLine() { return multiLine; }
	void SetMultiLine(bool b) { multiLine = b; }

	bool GetVerticalScroll() { return verticalScroll; }
	void SetVerticalScroll(bool b) { verticalScroll = b; }

	bool GetReadOnly() { return readOnly; }
	void SetReadOnly(bool b) {
		readOnly = b;

		if (GetSelf())
			SendMessage(GetSelf(), EM_SETREADONLY, readOnly, 0);
	}

	TextAlignment GetTextAlignment() { return textAlignment; }
	void SetTextAlignment(TextAlignment ta) { textAlignment = ta; }

	void FocusBottom() {
		SendMessage(GetSelf(), EM_SETSEL, 0, -1); // Select
		SendMessage(GetSelf(), EM_SETSEL, -1, -1); // Unselect
		SendMessage(GetSelf(), EM_SCROLLCARET, 0, 0); // Set caret		
	}

	const LPCWSTR GetNewLine() { return L"\r\n"; }

	TextBox() {
		SetClassname(L"EDIT");
		SetStyle(WS_VISIBLE | WS_CHILD | ES_LEFT | ES_AUTOVSCROLL);
		SetBorder(true);

		SetMultiLine(false);
		SetVerticalScroll(false);
		SetReadOnly(false);

		text = nullptr;
		textAlignment = ALIGNLEFT;
	}
	virtual ~TextBox() {
		ClearText();
	}

private:
	bool BeforeCreate(Item* parent) override {
		DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL;
		if (multiLine)
			dwStyle |= ES_MULTILINE;
		if (verticalScroll)
			dwStyle |= WS_VSCROLL;
		if (readOnly)
			dwStyle |= ES_READONLY;

		if (textAlignment == ALIGNCENTER)
			dwStyle |= ES_CENTER;
		else if (textAlignment == ALIGNRIGHT)
			dwStyle |= ES_RIGHT;
		else
			dwStyle |= ES_LEFT;

		SetStyle(dwStyle);
		return true;
	}
	bool AfterCreate() override {
		if (text)
			SetText(text);

		return true;
	}
};