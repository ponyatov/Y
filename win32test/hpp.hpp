#include <iostream>
#include <windows.h>
#include <vector>
#include <map>
using namespace std;

struct WinClass {
	WNDCLASS wc;
	WinClass();
};

struct Window {
	string Title;
	WinClass wndclass;
	static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
	Window(string T);
};

struct WinApplication {
	static char AppName[];
	static HINSTANCE hInstance;
	static LPSTR cmdLine;
	static int iCmdShow;
	WinApplication(HINSTANCE,LPSTR,int);
	static int run();
	map<string,Window*> wins;
	WinApplication& operator+=(Window* wnd);
};
