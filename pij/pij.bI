
TITLE = 'PIJ sample'
ABOUT = 'computing core for http://ikp.ssau.ru project: test bI metafunctions'
GITHUB = 'https://github.com/ponyatov/Y/tree/dev/pij/'
COLOR = 'peachpuff'

next		= dir @ 'next'					# module next generation

.inc ../lex/readme
.inc ../lex/meta
.inc ../lex/win32rc

.inc ../lex/hpp
.inc ../lex/cpp
.inc ../lex/tinymake

#.inc ../lex/parser
#.inc ../lex/lexer

files = [
#	MODULE+'.bI' MODULE+'.blog'
#	'../ypp.ypp' '../lpp.lpp' '../hpp.hpp' '../cpp.cpp' #'Makefile'
	hpp cpp make
	'bat.bat' meta readme
]

.inc ../lex/bat
