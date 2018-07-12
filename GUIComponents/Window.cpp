#include "stdafx.h"
#include "Window.h"


Window::Window()
{
	self = nullptr;

	SetClassname(L"WindowClass");
	SetTitle(L"WindowTitle");
}

Window::~Window()
{
	if (self)
		DestroyWindow(self);
}

bool Window::Create(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Window::StaticProcedure;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(Window*);
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = GetClassname();
	wcex.hIconSm = NULL;

	RegisterClassExW(&wcex);

	self = CreateWindowW(GetClassname(), GetTitle(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!self)
		return false;

	SetWindowLongPtr(self, 0, (LONG)this);

	ShowWindow(self, nCmdShow);
	UpdateWindow(self);

	return true;
}

bool Window::Initialize()
{
	if (!self)
		return false;

	return true;
}

bool Window::Update()
{
	if (!self)
		return false;

	return true;
}

LRESULT CALLBACK Window::Procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK Window::StaticProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* window = (Window*)GetWindowLongPtr(hWnd, 0);
	if (!window)
		return DefWindowProc(hWnd, message, wParam, lParam);
	else
		return window->Procedure(hWnd, message, wParam, lParam);
}
