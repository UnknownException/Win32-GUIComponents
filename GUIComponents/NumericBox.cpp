#include "stdafx.h"
#include "NumericBox.h"

NumericBox::NumericBox()
{
	textBox = nullptr;
}

NumericBox::~NumericBox()
{
	if (textBox)
		delete textBox;
}

bool NumericBox::Create()
{
	if (!RegisterControls())
		return false;

	if (GetParent() == nullptr)
		return false;

	textBox = new TextBox();
	textBox->SetParent(GetParent());
	textBox->SetPosition(GetPosition());
	textBox->SetSize(GetSize());
	textBox->SetReadOnly(true);
	if (!textBox->Create())
		return false;

	SetSelf(CreateWindowEx(NULL, L"msctls_updown32", L"", WS_VISIBLE | WS_CHILD | UDS_AUTOBUDDY | UDS_SETBUDDYINT | UDS_ALIGNRIGHT | UDS_ARROWKEYS | UDS_HOTTRACK,
		GetPosition().x, GetPosition().y, GetSize().x, GetSize().y, GetParent(), NULL, NULL, NULL));

	return GetSelf() != nullptr;
}