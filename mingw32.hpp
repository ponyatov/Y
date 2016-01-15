#ifndef _H_MINGW32
#define _H_MINGW32

#include <direct.h>
#include <windows.h>

struct Window:Sym { Window(Sym*); 		// create window (hided)
	string tagval();
										// == WINAPI specific ==
	HWND hwnd;							// winapi window id										
	static WNDCLASS wndclass;			// window class
	static const char wndClassName[];	// MODULE "window";
	static void regclass();				// register window class
	static MSG msg;						// == (async) messages ==
	static void dispatcher();			// window mainloop
	static LRESULT CALLBACK winproc(HWND, UINT, WPARAM, LPARAM);
										
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
};

struct Message:Sym { Message(Sym*); };	// message

#endif // _H_MINGW32
