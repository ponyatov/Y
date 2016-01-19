#include "hpp.hpp"

// ======================================================================= GUI

// --------------------------------------- message to system bar / message box

Sym* message(Sym*o) { return new Message(o); }

Message::Message(Sym*o):Sym("message",o->val) {}
string Message::tagval() { return tagstr(); }

// --------------------------------------- window

Sym* window(Sym*o) { return new Window(o); }

Window::Window(Sym*o):Sym("window",o->val) {}
string Window::tagval() { return tagstr(); }

