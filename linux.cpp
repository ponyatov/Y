#include "hpp.hpp"

// ==================================================================== FILEIO

Dir::Dir(Sym*o):Sym("dir",o->val) {
	assert(0==mkdir(val.c_str(),0700)||errno==EEXIST); }

// ======================================================================= GUI

// ======================================= message to system bar / message box

Message::Message(Sym*o):Sym("message",o->val) {}
