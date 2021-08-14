#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class ComboBox : public Item {
	std::vector<LPCWSTR> _content; // Contains a copy of the combobox items, at the cost of a little bit more memory usage
	int _selection;

	void ClearContent() {
		for(auto it = _content.begin(); it != _content.end(); ++it)
			delete[] *it;

		_content.clear();		
	}

	void AddStringToWin32Component(LPCWSTR string) {
		if (GetSelf()) {
			if (static_cast<int>(SendMessage(GetSelf(), CB_GETCOUNT, 0, 0)) == 0)
				SetWindowText(GetSelf(), string);

			SendMessage(GetSelf(), CB_ADDSTRING, 0, (LPARAM)string);
		}		
	}
public:
	LPCWSTR GetString(int index) {
		if(index < 0 || index >= static_cast<int>(_content.size()))
			return nullptr;
		
		return _content[index];
	}
	void AddString(LPCWSTR string) {
		WCHAR* output = new WCHAR[wcslen(string) + 1];
		wcscpy_s(output, wcslen(string) + 1, string);
			
		AddStringToWin32Component(output);

		_content.push_back(output);
	}

	int GetSelection() { return _selection; }
	void SetSelection(int index) {
		_selection = index;
		
		if (GetSelf())
			SendMessage(GetSelf(), CB_SETCURSEL, (WPARAM)_selection, 0);
	}

	int GetCount() { return static_cast<int>(_content.size()); }
		
	ComboBox() {
		SetClassname(L"COMBOBOX");
		SetStyle(WS_VISIBLE | WS_CHILD | WS_OVERLAPPED | WS_VSCROLL | CBS_DROPDOWN | CBS_HASSTRINGS);

		_selection = 0;
	}
	virtual ~ComboBox() {
		ClearContent();
	}
	
private:
	virtual bool BeforeCreate() override { return true; }
	bool AfterCreate() override {
		for (auto it = _content.begin(); it != _content.end(); ++it)
			AddStringToWin32Component(*it);

		if (_selection >= 0 && _selection < GetCount())
			SetSelection(_selection);

		return true;
	}	
};