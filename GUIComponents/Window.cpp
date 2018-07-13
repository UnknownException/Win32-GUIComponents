#include "stdafx.h"
#include "Window.h"

Window::Window()
{
	SetClassname(L"WindowClass");
	SetTitle(L"WindowTitle");

	resizable = true;
	minimizable = true;
	maximizable = true;
}

Window::~Window()
{
	SetWindowLongPtr(GetSelf(), 0, (LONG)nullptr);
}

bool Window::Create()
{
	return Create(GetModuleHandle(NULL), SW_SHOWDEFAULT);
}

bool Window::Create(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Window::StaticProcedure;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = sizeof(Window*); // For 'this' pointer in StaticProcedure
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = GetClassname();
	wcex.hIconSm = NULL;

	RegisterClassExW(&wcex);

	DWORD windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	if (resizable)
		windowStyle |= WS_THICKFRAME;
	if(minimizable)
		windowStyle |= WS_MINIMIZEBOX;
	if(maximizable)
		windowStyle |= WS_MAXIMIZEBOX;

	SetSelf(CreateWindowW(GetClassname(), GetTitle(), windowStyle,
				GetPosition().x, GetPosition().y, GetSize().x, GetSize().y, nullptr, nullptr, hInstance, nullptr));

	if (!GetSelf())
		return false;

	SetWindowLongPtr(GetSelf(), 0, (LONG)this);

	ShowWindow(GetSelf(), nCmdShow);
	UpdateWindow(GetSelf());

	return true;
}

bool Window::Initialize()
{
	if (!GetSelf())
		return false;

	return true;
}

bool Window::Update()
{
	if (!GetSelf())
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
