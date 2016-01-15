#include "hpp.hpp"

Window::Window(Sym*o):Sym("window",o->val) {

}

void Window::show() { par["show"]=nil; }

int WINAPI WinMain(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR CmdLine,
		int nCmdShow
	) {
	cout << "hInstance="<<hInstance<<"\n";
	cout << "hPrevInstance="<<hPrevInstance<<"\n";
	cout << "CmdLine="<<CmdLine<<"\n";
	cout << "nCmdShow="<<nCmdShow<<"\n";
	return 0;
}
