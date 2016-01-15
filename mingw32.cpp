#include "hpp.hpp"

static struct {							// == application WinMain (parameters)
	HINSTANCE hInstance;				// application id
	HINSTANCE hPrevInstance;			// 0 or app forked id
	LPSTR CmdLine;						// command line string (with spaces)
	int nCmdShow;
} WinMainParameters;

WNDCLASS Window::wndclass = {
	.style = 0,								// window style
	.lpfnWndProc = (WNDPROC) winproc,		// win message proc function
	.cbClsExtra = 0, .cbWndExtra = 0,		// extra data area sizes
};
const char Window::wndClassName[] = MODULE "window";

LRESULT CALLBACK Window::winproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	return DefWindowProc(hwnd,msg,wp,lp);
}

void Window::regclass() {					// == register window class ==
//	memset(&wndclass,0,sizeof(wndclass));	// clear struct
	wndclass.hInstance = WinMainParameters.hInstance;	// set app hInstance
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// load std icon
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);		// window cursor
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);// back color
	wndclass.lpszMenuName = (LPSTR)NULL;				// empty menu
	ATOM aWndClass = RegisterClass(&wndclass) ; // register
	assert(aWndClass);
}

Window::Window(Sym*o):Sym("window",o->val) {
	assert ( hwnd = CreateWindow(
			wndClassName,
			val.c_str(),					// title
			WS_OVERLAPPEDWINDOW,			// style
    		CW_USEDEFAULT,       			// \ geometry
    		CW_USEDEFAULT,
		    CW_USEDEFAULT,
		    CW_USEDEFAULT,					// /
    		0,                   			// parent window id
    		0,                   			// menu id
    		WinMainParameters.hInstance,	// application id
    		NULL));							// extra params
	ShowWindow(hwnd,WinMainParameters.nCmdShow);	// display window
}

void Window::show() { par["show"]=nil; }

MSG Window::msg;
void Window::dispatcher() {
	while (GetMessage(&msg,0,0,0)) {
		DispatchMessage(&msg);
	}
}

Message::Message(Sym*o):Sym("message",o->val) {
	MessageBox(NULL, val.c_str(), tag.c_str(), MB_OK);
}

int WINAPI WinMain(
		HINSTANCE hInstance,HINSTANCE hPrevInstance,
		LPSTR CmdLine,int nCmdShow) {
	// copy WinMain parameters
	WinMainParameters.hInstance = hInstance;
	WinMainParameters.hPrevInstance = hPrevInstance;
	WinMainParameters.CmdLine = CmdLine;
	WinMainParameters.nCmdShow = nCmdShow;
	// register app-wide objects
	Window::regclass();								// register window class
	// debug write
	cout << "hInstance="<<hInstance<<"\n";
	cout << "hPrevInstance="<<hPrevInstance<<"\n";
	cout << "CmdLine="<<CmdLine<<"\n";
	cout << "nCmdShow="<<nCmdShow<<"\n";
	// parser start
	env_init(); incLude(new Str(CmdLine)); return yyparse();
}
