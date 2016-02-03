#include "hpp.hpp"

// ==================================================================== FILEIO

Dir::Dir(Sym*o):Sym("dir",o->val) { mkdir(val.c_str()); }

