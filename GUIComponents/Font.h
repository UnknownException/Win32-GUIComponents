#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Font {
	LPWSTR name;
	int size;
	bool bold;
public:
	LPCWSTR GetName() { return name; }
	void SetName(LPCWSTR font) {
		if (name)
			delete[] name;

		name = new WCHAR[wcslen(font) + 1];
		wcscpy_s(name, wcslen(font) + 1, font);		
	}

	int GetSize() { return size; }
	void SetSize(int n) { size = n; }

	bool GetBold() { return bold; }
	void SetBold(bool b) { bold = b; }

	HFONT CreateInstance(HDC hDC) {
		if (!hDC)
			return nullptr;

		LOGFONTW lFnt;
		ZeroMemory(&lFnt, sizeof(LOGFONTW));

		lFnt.lfHeight = -MulDiv(GetSize(), GetDeviceCaps(hDC, LOGPIXELSY), 72);
		lFnt.lfWeight = GetBold() ? FW_BOLD : FW_NORMAL;
		wcscpy_s(lFnt.lfFaceName, sizeof(lFnt.lfFaceName) / sizeof(WCHAR), GetName());

		return CreateFontIndirectW(&lFnt);
	}
	
	Font() {
		SetName(L"");
		SetSize(10);
		SetBold(false);		
	}
	virtual ~Font() {
		if (name)
			delete[] name;		
	}
};