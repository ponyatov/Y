hpp	= next + file @ 'hpp.hpp'							# .hpp file structure
hpp += '#ifndef _H_'+upcase@MODULE+'\n'
hpp += '#define _H_'+upcase@MODULE+'\n'
hpp += '\n#include "meta.hpp"\n'
hpp += '
#include <iostream>
using namespace std;
'
hpp += '\n#include "../../'+OS+'.hpp"\t// target OS specific\n\n'
hpp += '#endif // _H_'+upcase@MODULE+'\n'

