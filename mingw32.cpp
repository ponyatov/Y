#include "hpp.hpp"

LRESULT CALLBACK WinClass::WndProc(HWND hwnd,UINT iMsg,WPARAM wp,LPARAM lp) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch (iMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			GetClientRect(hwnd,&rect);
			DrawText(hdc,MODULE,-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			EndPaint(hwnd,&ps);
			return 0;
		default:
			return DefWindowProc(hwnd,iMsg,wp,lp);
	}
}

Window::Window(Sym*o):Sym("window",o->val) {
	assert ( hwnd = CreateWindow(					// == create window ==
		WinApplication::AppName,					// window class
		val.c_str(),								// window title
		WS_OVERLAPPEDWINDOW,						// style
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,//geometry
		NULL,										// parent win
		NULL,										// menu
		WinApplication::hInstance,
		NULL
	));
	WinClass::wins.push_back(&hwnd);				// register for cleanup
	ShowWindow(hwnd,WinApplication::nCmdShow);		// display window
	MSG msg;
	while (GetMessage(&msg,0,0,0)) {				// infty msg dispatcher
		DispatchMessage(&msg);
	}
}

