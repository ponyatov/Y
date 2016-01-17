#include <iostream>
#include <windows.h>
using namespace std;

struct WinApplication {
	static HINSTANCE hInstance;
	static LPSTR cmdLine;
	WinApplication(HINSTANCE,LPSTR);
	int mainloop();
};

struct Window {
	string Title;
	Window(string T);
};
