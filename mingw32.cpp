#include "hpp.hpp"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
		LPSTR CmdLine,int nCmdShow) {
	// copy params to static class
	WinApp.hInstance=hInstance;
	WinApp.cmdLine=CmdLine;
	WinApp.nCmdShow=nCmdShow;
	// start REPL
	env_init(); return yyparse();
//	env_init(); incLude(new Str(CmdLine)); return yyparse();
}

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

WinClass::WinClass() {
	memset(&wc,0,sizeof(wc));
	wc.lpszClassName	= WinApplication::AppName;
	wc.hInstance		= WinApplication::hInstance;	
	wc.lpfnWndProc		= WndProc;
//	wc.cbClsExtra		= 0;
//	wc.cbWndExtra		= 0;
//	wc.style			= CS_HREDRAW|CS_VREDRAW;
//	wc.lpszMenuName		= NULL;
	wc.hIcon			= LoadIcon(WinApplication::hInstance,"logo");
	wc.hCursor			= LoadCursor(NULL,IDC_ARROW);
//	wc.hbrBackground	= (HBRUSH)GetStockObject(NULL_BRUSH);
	assert(RegisterClass(&wc));
}

vector<HWND*> WinClass::wins;						// hwnd registry
WinClass::~WinClass() {								// unregister window class
	for (auto wn=wins.begin(),e=wins.end();wn!=e;wn++)	// destroy windows
		DestroyWindow(**wn);
	assert(UnregisterClass(
		WinApplication::AppName,WinApplication::hInstance ));
}

WinApplication WinApp;
const char WinApplication::AppName[] = MODULE;		// application name 
HINSTANCE WinApplication::hInstance=0;				// winapp id
LPSTR WinApplication::cmdLine=0;					// command line
int WinApplication::nCmdShow=0;						// normal/full/iconized
WinClass WinApplication::winclass;					// shared window class

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

Window::~Window() { DestroyWindow(hwnd); }

Message::Message(Sym*o):Sym("message",o->val) {
	MessageBox(NULL, val.c_str(), tag.c_str(), MB_OK);
}
