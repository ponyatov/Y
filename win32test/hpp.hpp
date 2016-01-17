#include <iostream>
#include <cassert>
#include <windows.h>
#include <vector>
#include <map>
using namespace std;

struct Window {
	string Title;
	HWND hwnd;
	Window(string T);
	~Window();
};

struct WinClass {
	WNDCLASS wc;
	ATOM atom;
	static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
	WinClass();
	~WinClass();
};

struct WinApplication {
	static char AppName[];
	static HINSTANCE hInstance;
	static LPSTR cmdLine;
	static int iCmdShow;
	WinApplication(HINSTANCE,LPSTR,int);
	static int run();
	static WinClass winclass;
	static LRESULT CALLBACK quit();
	static map<string,Window*> wins;
	WinApplication& operator+=(Window* wnd);
};
