#include "hpp.hpp"

// ==================================================================== FILEIO

Dir::Dir(Sym*o):Sym("dir",o->val) {
	assert(0==mkdir(val.c_str())||errno==EEXIST); }

Sym* Dir::add(Sym*o) { 
//	File* F = new File(val+'/'+o->val);
	o->partag(Wr); o->partag(this); push(o);
	assert (o->tag=="file");
	assert( dynamic_cast<File*>(o)->fh = fopen( (val+'/'+o->val).c_str(),"w") );
	return o; }

// ======================================================================= GUI

// ======================================= message to system bar / message box

Message::Message(Sym*o):Sym("message",o->val) {
	MessageBox(NULL, val.c_str(), tag.c_str(), MB_OK);
}

