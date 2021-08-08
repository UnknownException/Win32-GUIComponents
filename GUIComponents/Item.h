#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Item {
	HWND _parent;
	HWND _self;

	LPWSTR _classname;
	LPWSTR _title;

	DWORD _style;

	Vector2<int> _position;
	Vector2<int> _size;

	bool _border;
	bool _visible;
	bool _enabled;

	Font* _font;

public:
	HWND GetParent() { return _parent; }
	void SetParent(HWND parent) { _parent = parent; }

protected:
	HWND GetSelf() { return _self; }
	void SetSelf(HWND self) { _self = self; }

	LPCWSTR GetClassname() { return _classname; }
	void SetClassname(LPCWSTR classname) {
		if (_classname)
			delete[] _classname;

		_classname = new WCHAR[wcslen(classname) + 1];
		wcscpy_s(_classname, wcslen(classname) + 1, classname);
	}

	LPCWSTR GetTitle() { return _title; }
	void SetTitle(LPCWSTR title) {
		if (_title)
			delete[] _title;

		_title = new WCHAR[wcslen(title) + 1];
		wcscpy_s(_title, wcslen(title) + 1, title);

		if (GetSelf())
			SetWindowText(GetSelf(), _title);
	}

	DWORD GetStyle() { return _style; }
	void SetStyle(DWORD style) { _style = style; }

	bool GetBorder() { return _border; }
	void SetBorder(bool border) { _border = border; }

public:
	decltype(_position) GetPosition() { return _position; }
	void SetPosition(decltype(_position) position) { _position = position; }

	decltype(_size) GetSize() { return _size; }
	void SetSize(decltype(_size) size) { _size = size; }

	bool GetVisible() { return _visible; }
	void SetVisible(bool visible) {
		_visible = visible;

		if(GetSelf())
			ShowWindow(GetSelf(), _visible ? SW_SHOWDEFAULT : SW_HIDE);
	}

	bool GetEnabled() { return _enabled; }
	void SetEnabled(bool enabled) {
		_enabled = enabled;

		if(GetSelf())
			EnableWindow(GetSelf(), _enabled);
	}

	Font* GetFont() { return _font; }
	void SetFont(Font* font) {
		_font = font;
		if (GetSelf()) {
			if (_font && !_font->_GetInstance()) {
				HDC hDC = GetDC(GetSelf());
				_font->_CreateInstance(hDC);
				ReleaseDC(GetSelf(), hDC);
			}

			SendMessage(GetSelf(), WM_SETFONT, _font ? (WPARAM)_font->_GetInstance() : NULL, (LPARAM)MAKELONG(TRUE, 0));
		}
	}

	bool IsSame(HWND hWnd) { return _self == hWnd; }
	bool Create() { return Create(NULL); }

public:
	Item() {
		SetParent(nullptr);
		SetSelf(nullptr);

		SetClassname(L"");
		SetTitle(L"");

		SetStyle(0);

		SetBorder(false);
		SetVisible(true);
		SetEnabled(true);

		_font = nullptr;
	}
	virtual ~Item() {
		if (_self)
			DestroyWindow(_self);

		if (_classname)
			delete[] _classname;

		if (_title)
			delete[] _title;
	}

protected:
	virtual bool BeforeCreate() = 0; // Before HWND self is set
	bool Create(HINSTANCE hInstance) {
		if (!RegisterControls())
			return false;

		if (hInstance == NULL && !GetParent())
			return false;

		if (!BeforeCreate())
			return false;

		SetSelf(CreateWindowEx(GetBorder() ? WS_EX_CLIENTEDGE : NULL, GetClassname(), GetTitle(), GetStyle(),
			GetPosition().x, GetPosition().y, GetSize().x, GetSize().y, GetParent(), NULL, hInstance, NULL));

		if (!GetSelf())
			return false;

		SetVisible(GetVisible());
		SetEnabled(GetEnabled());
		SetFont(_font);

		if (!AfterCreate())
			return false;

		return true;
	}
	virtual bool AfterCreate() = 0; // After HWND self is set

private:
	static bool RegisterControls() {
		static bool registered = false;
		if (registered)
			return registered;

		INITCOMMONCONTROLSEX icex;
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_STANDARD_CLASSES;
		if (!InitCommonControlsEx(&icex))
			return false;

		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_UPDOWN_CLASS;
		if (!InitCommonControlsEx(&icex))
			return false;

		registered = true;
		return registered;
	}
};