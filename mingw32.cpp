#include "hpp.hpp"

Window::Window(Sym*o):Sym("window",o->val) {

}

void Window::show() { par["show"]=nil; }

static struct {
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance;
	LPSTR CmdLine;
	int nCmdShow;
} WinMainParameters;

int WINAPI WinMain(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR CmdLine,
		int nCmdShow
	) {
	// copy WinMain parameters
	WinMainParameters.hInstance = hInstance;
	WinMainParameters.hPrevInstance = hPrevInstance;
	WinMainParameters.CmdLine = CmdLine;
	WinMainParameters.nCmdShow = nCmdShow;
	// debug write
	cout << "hInstance="<<hInstance<<"\n";
	cout << "hPrevInstance="<<hPrevInstance<<"\n";
	cout << "CmdLine="<<CmdLine<<"\n";
	cout << "nCmdShow="<<nCmdShow<<"\n";
	// parser start
	env_init(); incLude(new Str(CmdLine)); return yyparse();
}
