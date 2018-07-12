#pragma once
#include "Vector2.h"

class Item {
	HWND parent;
	HWND self;

	Vector2<int> position;
	Vector2<int> size;
public:
	Item();
	virtual ~Item();

	HWND GetParent() { return parent; }
	void SetParent(HWND p) { parent = p; }

protected:
	HWND GetSelf() { return self; }
	void SetSelf(HWND s) { self = s; }

public:
	decltype(position) GetPosition() { return position; }
	void SetPosition(decltype(position) p) { position = p; }

	decltype(size) GetSize() { return size; }
	void SetSize(decltype(size) s) { size = s; }

	virtual bool Create() = 0;
	bool IsSame(HWND hWnd) { return self == hWnd; }
};
