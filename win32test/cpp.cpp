#include "hpp.hpp"

HINSTANCE WinApplication::hInstance=0;
LPSTR WinApplication::cmdLine=0;

WinApplication::WinApplication(HINSTANCE H, LPSTR L) {
	hInstance = H; cmdLine = L;
}

int WinApplication::mainloop() {
	return 0;
}

int WINAPI WinMain (HINSTANCE hInstance,HINSTANCE,LPSTR cmdLine,int) {
	return WinApplication(hInstance,cmdLine).mainloop();
}
