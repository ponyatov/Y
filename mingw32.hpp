#ifndef _H_MINGW32
#define _H_MINGW32

#include <direct.h>
#include <windows.h>

struct Window:Sym { Window(Sym*); 		// window
	string tagval();
	void show();
};

struct Message:Sym { Message(Sym*); };	// message

#endif // _H_MINGW32
