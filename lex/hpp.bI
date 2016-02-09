hpp	= next + file @ 'hpp.hpp'							# .hpp file structure
hpp += '#ifndef _H_'+upcase@MODULE+'\n'
hpp += '#define _H_'+upcase@MODULE+'\n'
hpp += '#include "meta.hpp"\n'
hpp += '
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
using namespace std;
'
#hpp += '\n#include "../../'+OS+'.hpp"\t// target OS specific\n\n'
hpp += objects/'\n'+'\n'
hpp += lex_hpp
hpp += yacc_hpp
hpp += '#endif // _H_'+upcase@MODULE+'\n'

