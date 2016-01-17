#include "hpp.hpp"

char WinApplication::AppName[] = MODULE;
HINSTANCE WinApplication::hInstance=0;
LPSTR WinApplication::cmdLine=0;
int WinApplication::iCmdShow=0;

WinApplication::WinApplication(HINSTANCE H, LPSTR L, int S) {
	hInstance = H; cmdLine = L; iCmdShow = S;
	cerr << AppName << "[" << cmdLine << "]:" << iCmdShow <<"\n";
}

int WinApplication::run() {
	return 0;
}

WinApplication& WinApplication::operator+=(Window* wnd) { wins[wnd->Title]=wnd; }

WinClass::WinClass() {}

Window::Window(string T) {
	Title=T;
}

int WINAPI WinMain (HINSTANCE hInstance,HINSTANCE,LPSTR cmdLine,int iCmdShow) {
	WinApplication app(hInstance,cmdLine,iCmdShow);
	app += new Window("main");
	return app.run();
}
