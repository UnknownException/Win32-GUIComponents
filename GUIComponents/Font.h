#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Font {
	LPWSTR _name;
	int _size;
	bool _bold;

	HFONT _fontInstance;
public:
	LPCWSTR GetName() { return _name; }
	void SetName(LPCWSTR name) {
		if (_name)
			delete[] _name;

		_name = new WCHAR[wcslen(name) + 1];
		wcscpy_s(_name, wcslen(name) + 1, name);
	}

	int GetSize() { return _size; }
	void SetSize(int n) { _size = n; }

	bool GetBold() { return _bold; }
	void SetBold(bool b) { _bold = b; }

	void CreateInstance(HDC hDC) {
		LOGFONTW lFnt;
		ZeroMemory(&lFnt, sizeof(LOGFONTW));

		lFnt.lfHeight = hDC ? -MulDiv(GetSize(), GetDeviceCaps(hDC, LOGPIXELSY), 72) : 0;
		lFnt.lfWeight = GetBold() ? FW_BOLD : FW_NORMAL;
		wcscpy_s(lFnt.lfFaceName, sizeof(lFnt.lfFaceName) / sizeof(WCHAR), GetName());

		_fontInstance = CreateFontIndirectW(&lFnt);
	}

	HFONT GetInstance() { return _fontInstance; }
	
	Font() {
		SetName(L"");
		SetSize(10);
		SetBold(false);	

		_fontInstance = nullptr;
	}
	virtual ~Font() {
		if (_name)
			delete[] _name;	

		if (_fontInstance)
			DeleteObject(_fontInstance);	
	}
};