#include "stdafx.h"
#include "Checkbox.h"

Checkbox::Checkbox()
{
	SetText(L"Button");
	SetCheck(false);
}

Checkbox::~Checkbox()
{
}

bool Checkbox::GetCheck()
{
	if (GetSelf() != nullptr)
		return SendMessage(GetSelf(), BM_GETCHECK, 0, 0);

	return preCheck;
}

void Checkbox::SetCheck(bool s)
{
	if (GetSelf() != nullptr)
		SendMessage(GetSelf(), BM_SETCHECK, (WPARAM)s, 0);
	else
		preCheck = s;
}

bool Checkbox::Create()
{
	if (!RegisterControls())
		return false;

	if (GetParent() == nullptr)
		return false;

	SetSelf(CreateWindowEx(NULL, L"BUTTON", GetText(), WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 
				GetPosition().x, GetPosition().y, GetSize().x, GetSize().y, GetParent(), NULL, NULL, NULL));

	if (GetSelf())
		SetCheck(preCheck);

	return GetSelf() != nullptr;
}