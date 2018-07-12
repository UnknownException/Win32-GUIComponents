#pragma once
#include "Item.h"

class Checkbox : public Item {
	LPCWSTR text;
	bool preCheck;
public:
	Checkbox();
	virtual ~Checkbox();

	LPCWSTR GetText() { return text; }
	void SetText(LPCWSTR t) { text = t; }

	bool GetCheck();
	void SetCheck(bool s);

	bool Create() override;
};