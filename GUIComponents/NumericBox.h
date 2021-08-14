#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class NumericBox : public Item {
	TextBox* textBox;
	int min;
	int max;
	int preSelection;

public:
	int GetMin() { return min; }
	void SetMin(int value) {
		min = value;

		if (GetSelf())
			SendMessage(GetSelf(), UDM_SETRANGE32, min, max);
	}

	int GetMax() { return max; }
	void SetMax(int value) {
		max = value;

		if (GetSelf())
			SendMessage(GetSelf(), UDM_SETRANGE32, min, max);
	}

	int GetSelection() {
		if (!GetSelf())
			return preSelection;

		return (int)SendMessage(GetSelf(), UDM_GETPOS32, 0, 0);
	}
	void SetSelection(int value) {
		if (!GetSelf())
			preSelection = value;
		else
			SendMessage(GetSelf(), UDM_SETPOS32, 0, value);
	}

	NumericBox() {
		SetClassname(L"msctls_updown32");
		SetStyle(WS_VISIBLE | WS_CHILD | UDS_AUTOBUDDY | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK);

		textBox = nullptr;

		min = 0;
		max = 100;
		preSelection = 0;
	}
	virtual ~NumericBox() {
		if (textBox)
			delete textBox;
	}
	
private:
	/*
		Creates a Text Box before the Up Down Control is made
		The Up Down Control will bind to this Text Box
	*/
	virtual bool BeforeCreate(Item* parent) override {
		textBox = new TextBox();
		textBox->SetPosition(GetPosition());
		textBox->SetSize(GetSize());
		textBox->SetReadOnly(true);
		textBox->SetTextAlignment(TextBox::ALIGNCENTER);

		return textBox->Create(parent);
	}
	virtual bool AfterCreate() override {
		SetMin(GetMin());
		SetMax(GetMax());

		SetSelection(preSelection);

		return true;
	}
};