#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class ComboBox : public Item {
	std::vector<LPCWSTR> preStrings;
	int preSelection;

	void ClearPreSelection() {
		for(auto it = preStrings.begin(); it != preStrings.end(); ++it)
			delete[] *(it);

		preStrings.clear();		
	}

public:
	void AddString(LPCWSTR string) {
		if (GetSelf())
		{
			if (GetCount() == 0)
				SetWindowText(GetSelf(), string);

			SendMessage(GetSelf(), CB_ADDSTRING, 0, (LPARAM)string);
		}
		else
		{
			WCHAR* output = new WCHAR[wcslen(string) + 1];
			wcscpy_s(output, wcslen(string) + 1, string);
			preStrings.push_back(output);
		}
	}

	int GetSelection() {
		if (GetSelf())
			return static_cast<int>(SendMessage(GetSelf(), CB_GETCURSEL, 0, 0));

		return 0;
	}
	void SetSelection(int index) {
		if (GetSelf())
			SendMessage(GetSelf(), CB_SETCURSEL, (WPARAM)index, 0);
		else
			preSelection = index;
	}

	int GetCount() {
		if (GetSelf())
			return static_cast<int>(SendMessage(GetSelf(), CB_GETCOUNT, 0, 0));
		
		return static_cast<int>(preStrings.size());	
	}

	ComboBox() {
		SetClassname(L"COMBOBOX");
		SetStyle(WS_VISIBLE | WS_CHILD | WS_OVERLAPPED | WS_VSCROLL | CBS_DROPDOWN | CBS_HASSTRINGS);

		preSelection = -1;
	}
	virtual ~ComboBox() {
		ClearPreSelection();
	}
	
private:
	virtual bool BeforeCreate() override { return true; }
	bool AfterCreate() override {
		for (auto it = preStrings.begin(); it != preStrings.end(); ++it)
			AddString(*(it));

		if (preSelection >= 0 && preSelection < static_cast<int>(preStrings.size()))
			SetSelection(preSelection);

		ClearPreSelection();
		return true;
	}	
};