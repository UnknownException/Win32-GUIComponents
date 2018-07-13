#pragma once
#include "Item.h"

class Window : public Item {
	LPCWSTR classname;
	LPCWSTR title;
public:
	Window();
	virtual ~Window();

public:
	LPCWSTR GetClassname() { return classname; }
	void SetClassname(LPCWSTR c) { classname = c; }

	LPCWSTR GetTitle() { return title; }
	void SetTitle(LPCWSTR t) { title = t; }

	bool Create() override;
	virtual bool Create(HINSTANCE hInstance, int nCmdShow);
	virtual bool Initialize();
	virtual bool Update();

private:
	virtual LRESULT CALLBACK Procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK StaticProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};