#ifndef _H_MINGW32
#define _H_MINGW32

#include <direct.h>
#include <windows.h>

struct Window:Sym { Window(Sym*); 		// window
	string tagval();
	void show();
};

#endif // _H_MINGW32
