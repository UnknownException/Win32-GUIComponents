#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Window : public Item {
	bool resizable;
	bool minimizable;
	bool maximizable;

	HINSTANCE hInstance;
	int cmdShow;
public:
	bool GetResizable() { return resizable; }
	void SetResizable(bool b) { resizable = b; }

	bool GetMinimizable() { return minimizable; }
	void SetMinimizable(bool b) { minimizable = b; }

	bool GetMaximizable() { return maximizable; }
	void SetMaximizable(bool b) { maximizable = b; }

	Window() {
		resizable = true;
		minimizable = true;
		maximizable = true;

		hInstance = GetModuleHandle(NULL);
		cmdShow = SW_SHOWDEFAULT;
	}
	virtual ~Window() {
		SetWindowLongPtr(GetSelf(), 0, (LONG)nullptr);
	}

private:
	bool BeforeCreate() override {
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
		if (minimizable)
			windowStyle |= WS_MINIMIZEBOX;
		if (maximizable)
			windowStyle |= WS_MAXIMIZEBOX;

		SetStyle(windowStyle);
		return true;
	}
	bool AfterCreate() override {
		SetWindowLongPtr(GetSelf(), 0, (LONG_PTR)this);

		ShowWindow(GetSelf(), cmdShow);
		UpdateWindow(GetSelf());
		return true;
	}

public:
	bool Create(HINSTANCE hInstance, int nCmdShow) {
		hInstance = hInstance;
		cmdShow = nCmdShow;

		return Item::Create(hInstance);
	}
	virtual bool Initialize() {
		if (!GetSelf())
			return false;

		return true;
	}
	virtual bool Update() {
		if (!GetSelf())
			return false;

		return true;
	}

private:
	virtual LRESULT CALLBACK Procedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
		switch (message) {
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	static LRESULT CALLBACK StaticProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		Window* window = (Window*)GetWindowLongPtr(hWnd, 0);
		if (!window)
			return DefWindowProc(hWnd, message, wParam, lParam);
		else
			return window->Procedure(hWnd, message, wParam, lParam);
	}
};