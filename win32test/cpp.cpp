#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\\"
void yyerror(string msg) { cout<<YYERR; cerr<<YYERR; exit(-1); }
int main() { env_init(); return yyparse(); }

void W(Sym*o)		{ cout << o->dump(); }
void W(string s)	{ cout << s; }

string Sym::dump()	{ return tag+"@"+val; }

struct Window {
	static const char wndClass[];
	static const HINSTANCE hInstance;
	string Title;
	MSG msg;
	HWND hwnd;
	Window(string);
	void mainloop();
};

const char Window::wndClass[] = MODULE;
const HINSTANCE hInstance = GetModuleHandle(NULL);

Window::Window(string T) {
	Title = T;
	assert( hwnd = CreateWindow(
		wndClass,					// class name
		Title.c_str(),				// title
		WS_OVERLAPPEDWINDOW,		// style
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT, // geometry
		0,							// parent wnd
		0,							// menu id
		hApp,						// app hinst
		NULL						// extra params
	));
}

void Window::mainloop() {
	while(GetMessage(&msg,0,0,0))
		DispatchMessage(&msg);
}

