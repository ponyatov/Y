#include "hpp.hpp"

char WinApplication::AppName[] = MODULE;
HINSTANCE WinApplication::hInstance=0;
LPSTR WinApplication::cmdLine=0;
int WinApplication::iCmdShow=0;
WinClass WinApplication::winclass;
map<string,Window*> WinApplication::wins;

WinApplication::WinApplication(HINSTANCE H, LPSTR L, int S) {
	hInstance = H; cmdLine = L; iCmdShow = S;
	cerr << AppName << "[" << cmdLine << "]:" << iCmdShow <<"\n";
}

int WinApplication::run() {
	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
		DispatchMessage(&msg);
	return msg.wParam;
}

WinApplication& WinApplication::operator+=(Window* wnd) { wins[wnd->Title]=wnd; }

LRESULT CALLBACK WinApplication::quit() {
	for (auto wn=wins.begin(),e=wins.end();wn!=e;wn++)
		delete wn->second;
	PostQuitMessage(0);
	return 0;
}

LRESULT CALLBACK WinClass::WndProc(HWND hwnd,UINT iMsg,WPARAM wp,LPARAM lp) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	char b[0x10];
	int prevmsg;
	switch (iMsg) {
		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);	// gdi context
			GetClientRect(hwnd,&rect);
			DrawText(hdc,itoa(prevmsg,b,0x10),-1,&rect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			EndPaint(hwnd,&ps);
			return 0;
		case WM_DESTROY:
			WinApplication::quit();
		default:
			prevmsg=iMsg;
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
	assert(atom=RegisterClass(&wc));
}

WinClass::~WinClass() {
	assert(UnregisterClass(
		WinApplication::AppName,WinApplication::hInstance)); }

//vector<Window*> WinClass::wins;
Window::Window(string T) {
	Title="[" MODULE "] "+T;
	assert ( hwnd = CreateWindow(
		WinApplication::AppName,
		Title.c_str(),
		WS_OVERLAPPEDWINDOW,		// style
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,//geometry
		NULL,						// parent win
		NULL,						// menu
		WinApplication::hInstance,
		NULL
	));
	ShowWindow(hwnd,WinApplication::iCmdShow);
}

Window::~Window() { DestroyWindow(hwnd); }

int WINAPI WinMain (HINSTANCE hInstance,HINSTANCE,LPSTR cmdLine,int iCmdShow) {
	WinApplication app(hInstance,cmdLine,iCmdShow);
	app += new Window("main");
	app += new Window("log");
	return app.run();
}