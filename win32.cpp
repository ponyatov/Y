#include "hpp.hpp"

// ================================================================= WinMain()
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
		LPSTR CmdLine,int nCmdShow) {
	// copy params to static class
	WinApp.hInstance=hInstance;
	WinApp.cmdLine=CmdLine;
	WinApp.nCmdShow=nCmdShow;
	// start REPL
	env_init(); /* incLude(new Str(CmdLine)); */ return yyparse();
}

// ============================================== window application singleton
WinApplication WinApp;
const char WinApplication::AppName[] = MODULE;		// application name 
HINSTANCE WinApplication::hInstance=0;				// winapp id
LPSTR WinApplication::cmdLine=0;					// command line
int WinApplication::nCmdShow=0;						// normal/full/iconized
WinClass WinApplication::winclass;					// shared window class

// ======================================================= shared window class

LRESULT CALLBACK WinClass::WndProc(HWND hwnd,UINT iMsg,WPARAM wp,LPARAM lp) {
	return DefWindowProc(hwnd,iMsg,wp,lp);
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

// ======================================================================= GUI

// ======================================= message to system bar / message box

Sym* message(Sym*o) { return new Message(o); }

Message::Message(Sym*o):Sym("message",o->val) {
	MessageBox(NULL, val.c_str(), tag.c_str(), MB_OK);
}

string Message::tagval() { return tagstr(); }

// ==================================================================== window

Sym* window(Sym*o) { return new Window(o); }

Window::Window(Sym*o):Sym("window",o->val) {}
string Window::tagval() { return tagstr(); }
Window::~Window() { DestroyWindow(hwnd); }
