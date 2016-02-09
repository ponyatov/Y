hpp	= next + file @ 'hpp.hpp'							# .hpp file structure
hpp += '#ifndef _H_'+upcase@MODULE+'\n'
hpp += '#define _H_'+upcase@MODULE+'\n'
hpp += '#include "meta.hpp"\n'
hpp += '#include <iostream>\nusing namespace std;\n'
#hpp += '\n#include "../../'+OS+'.hpp"\t// target OS specific\n\n'
hpp += '#endif // _H_'+upcase@MODULE+'\n'

