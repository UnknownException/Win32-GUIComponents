#pragma once
#include "Item.h"

class TextBox : public Item {
	bool multiLine;
	bool verticalScroll;
	bool readOnly;
	LPCWSTR text;
public:
	TextBox();
	virtual ~TextBox();

private:
	void ClearText();

public:
	LPCWSTR GetText();
	void SetText(LPCWSTR string);
	void AppendText(LPCWSTR string);

	void SetMultiLine(bool b) { multiLine = b; }
	void SetVerticalScroll(bool b) { verticalScroll = b; }
	void SetReadOnly(bool b) { readOnly = b; }

	void FocusBottom();

	bool Create() override;

	const LPCWSTR GetNewLine() { return L"\r\n"; }
};