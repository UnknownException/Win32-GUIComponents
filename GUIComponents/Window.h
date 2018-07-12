#pragma once

class Window {
	HWND self;
	LPCWSTR classname;
	LPCWSTR title;
public:
	Window();
	virtual ~Window();

protected:
	HWND GetSelf() { return self; }

public:
	LPCWSTR GetClassname() { return classname; }
	void SetClassname(LPCWSTR c) { classname = c; }

	LPCWSTR GetTitle() { return title; }
	void SetTitle(LPCWSTR t) { title = t; }

	virtual bool Create(HINSTANCE hInstance, int nCmdShow);
	virtual bool Initialize();
	virtual bool Update();

private:
	virtual LRESULT CALLBACK Procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK StaticProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};