#include "hpp.hpp"

// ==================================================================== FILEIO

Dir::Dir(Sym*o):Sym("dir",o->val) {
	assert(0==mkdir(val.c_str())||errno==EEXIST); }

// ======================================================================= GUI

// ======================================= message to system bar / message box

Message::Message(Sym*o):Sym("message",o->val) {
	MessageBox(NULL, val.c_str(), tag.c_str(), MB_OK);
}
