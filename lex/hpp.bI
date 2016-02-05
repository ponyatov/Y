hpp	= next + file @ 'hpp.hpp'							# .hpp file structure
hpp += '#ifndef _H_'+upcase@MODULE+'\n'
hpp += '#define _H_'+upcase@MODULE+'\n'
hpp += '#include "meta.hpp"\n'
hpp += '#endif // _H_'+upcase@MODULE+'\n'

