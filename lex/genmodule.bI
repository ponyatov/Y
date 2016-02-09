
TITLE = 'genmodule'
ABOUT = 'script generates lexical skeleton (see genmodule.bat)'
GITHUB = 'https://github.com/ponyatov/Y/tree/dev/'+MODULE+'/'
LOGO = 'hedge64x64' # triangle Rubik_64x64 warning
COLOR = 'darkblue' # peachpuff

.sec Objects

objects = [
'struct Sym {};'
]

.sec Files

next		= dir @ 'next'					# module next generation

.inc ../lex/readme
.inc ../lex/meta
.inc ../lex/win32rc

#.inc ../lex/lexer
#.inc ../lex/parser
#.inc ../lex/hpp
#.inc ../lex/cpp
#.inc ../lex/make

files = [
	MODULE+'.bI' MODULE+'.blog'
	'../ypp.ypp' '../lpp.lpp' '../hpp.hpp' '../cpp.cpp' #'Makefile'
#	yacc lex hpp cpp make
	'bat.bat' meta readme
]

.inc ../lex/bat

