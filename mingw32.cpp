#include "hpp.hpp"

Window::Window(Sym*o):Sym("window",o->val) {}

void Window::show() { par["show"]=nil; }
