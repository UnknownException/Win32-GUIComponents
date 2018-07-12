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