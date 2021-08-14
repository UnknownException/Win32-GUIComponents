#pragma once

#ifndef _GUICOMPONENTS_HEADER
	#error Must include GUIComponents.h
#endif

class Window : public Item {
	bool _resizable;
	bool _minimizable;
	bool _maximizable;

	HINSTANCE _hInstance;
	int _cmdShow;

public:
	bool GetResizable() { return _resizable; }
	void SetResizable(bool resizable) { _resizable = resizable; }

	bool GetMinimizable() { return _minimizable; }
	void SetMinimizable(bool minimizable) { _minimizable = minimizable; }

	bool GetMaximizable() { return _maximizable; }
	void SetMaximizable(bool maximizable) { _maximizable = maximizable; }

	Window() {
		_resizable = true;
		_minimizable = true;
		_maximizable = true;

		_hInstance = GetModuleHandle(NULL);
		_cmdShow = SW_SHOWDEFAULT;
	}
	virtual ~Window() {
		SetWindowLongPtr(GetSelf(), 0, (LONG)nullptr);
	}

private:
	bool BeforeCreate(Item* parent) override {
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = Window::StaticProcessMessage;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = sizeof(Window*); // For 'this' pointer in StaticProcedure
		wcex.hInstance = _hInstance;
		wcex.hIcon = NULL;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = GetClassname();
		wcex.hIconSm = NULL;

		RegisterClassExW(&wcex);

		DWORD windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
		if (_resizable)
			windowStyle |= WS_THICKFRAME;
		if (_minimizable)
			windowStyle |= WS_MINIMIZEBOX;
		if (_maximizable)
			windowStyle |= WS_MAXIMIZEBOX;

		SetStyle(windowStyle);
		return true;
	}
	bool AfterCreate() override {
		SetWindowLongPtr(GetSelf(), 0, (LONG_PTR)this);

		ShowWindow(GetSelf(), _cmdShow);
		UpdateWindow(GetSelf());
		return true;
	}

public:
	bool Create(HINSTANCE hInst, int nCmdShow) {
		_hInstance = hInst;
		_cmdShow = nCmdShow;

		return Item::Create(_hInstance, NULL);
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

protected:
	virtual bool OnMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override {
		switch (message) {
			case WM_DESTROY:
				PostQuitMessage(0);
				return true;
		}

		return Item::OnMessage(hWnd, message, wParam, lParam);
	}

private:
	LRESULT CALLBACK ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
		if (OnMessage(hWnd, message, wParam, lParam))
			return 0;

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	static LRESULT CALLBACK StaticProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		Window* window = (Window*)GetWindowLongPtr(hWnd, 0);
		if (!window)
			return DefWindowProc(hWnd, message, wParam, lParam);
		else
			return window->ProcessMessage(hWnd, message, wParam, lParam);
	}
};