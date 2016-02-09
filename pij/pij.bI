
TITLE = 'PIJ sample'
ABOUT = 'computing core for http://ikp.ssau.ru project: test bI metafunctions'
GITHUB = 'https://github.com/ponyatov/Y/tree/dev/pij/'
COLOR = 'peachpuff'

.sec Objects

objects = [
'struct Sym {};'
'struct Scalar: Sym {};'
'struct Str: Scalar {};'
'struct Int: Scalar {};'
'struct Num: Scalar {};'
'struct List: Sym {};'
]

.sec Files

next		= dir @ 'next'					# module next generation

.inc ../lex/readme
#.inc ../lex/gitignore
.inc ../lex/meta
.inc ../lex/win32rc

#.inc ../lex/hpp
hpp	= next + file @ 'hpp.hpp'							# .hpp file structure
hpp += '#ifndef _H_'+upcase@MODULE+'\n'
hpp += '#define _H_'+upcase@MODULE+'\n'
hpp += '#include "meta.hpp"'
hpp += '
#include <iostream>
//#include <cstdlib>
//#include <cstdio>
//#include <cassert>
//#include <vector>
//#include <map>
using namespace std;
'
hpp += objects/'\n'+'\n'
hpp += '#endif // _H_'+upcase@MODULE+'\n'

#.inc ../lex/cpp
cpp	= next + file @ 'cpp.cpp'
cpp += '#include "hpp.hpp"\n'
cpp += 'int main(int argc, char *argv[]) {
	cerr << "\\n" << MODULE << " : " << TITLE << "\\n" << ABOUT << "\\n";
	cerr << /* (c) */ AUTHOR << "\\n\\n";
	return 0; }'

.inc ../lex/tinymake

files = [
#	MODULE+'.bI' MODULE+'.blog'
#	'../ypp.ypp' '../lpp.lpp' '../hpp.hpp' '../cpp.cpp' #'Makefile'
#	yacc lex 
	hpp cpp make
	'bat.bat' meta readme
]

.inc ../lex/bat

