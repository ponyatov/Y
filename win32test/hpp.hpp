#include <iostream>
#include <cassert>
#include <windows.h>
#include <vector>
#include <map>
using namespace std;

struct WinClass {
	WNDCLASS wc;
	ATOM atom;
	static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
	WinClass();
	~WinClass();
};

struct Window {
	string Title;
	HWND hwnd;
	WinClass wndclass;
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
