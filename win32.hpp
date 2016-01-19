#ifndef _H_WIN32
#define _H_WIN32

#include <direct.h>
#include <windows.h>

// ======================================================================= GUI

// --------------------------------------- message to system bar / message box
struct Message:Sym { Message(Sym*); string tagval(); 
};
extern Sym* message(Sym*);			

// --------------------------------------- window
struct Window:Sym { Window(Sym*); ~Window(); string tagval();
/*
	void hide();
	void show();
	void paint();						// repaint contents
	void iconize();						// minimize
	void maximize();					// fullscreen with decorations
	void fullscreen();					// game mode fullscreen
	void create();						// on window create
	void destroy();						// on window destroy
	void click();						// touch / left mouse click
	void popup();						// local popup menu / right mouse click
*/
										// == WINAPI specific ==
	HWND hwnd;							// winapi window id
};
extern Sym* window(Sym*);

// ============================================================================

// --------------------------------------- window class
struct WinClass {
	WinClass();
	~WinClass();
	static vector<HWND*> wins;			// window registry for cleanup
	WNDCLASS wc;
	static LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
};

// --------------------------------------- window application singleton
struct WinApplication {
	static const char AppName[];		// applicatio name
	static HINSTANCE hInstance;			// winapp id
	static LPSTR cmdLine;				// command line with spaces
	static int nCmdShow;				// startup normal/full/minimized
	static WinClass winclass;			// shared window class
};
extern WinApplication WinApp;

#endif // _H_WIN32
