#include "stdafx.h"
#include "Item.h"

Item::Item()
{
	parent = nullptr;
	self = nullptr;
}

Item::~Item()
{
	if (self)
		DestroyWindow(self);
}

void Item::SetVisible(bool b)
{
	ShowWindow(self, b ? SW_SHOWDEFAULT : SW_HIDE);
}

void Item::SetEnabled(bool b)
{
	EnableWindow(self, b);
}

bool Item::RegisterControls()
{
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
