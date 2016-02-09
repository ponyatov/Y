
TITLE = 'PIJ sample'
ABOUT = 'computing core for http://ikp.ssau.ru project: test bI metafunctions'
GITHUB = 'https://github.com/ponyatov/Y/tree/dev/pij/'
COLOR = 'darkblue'

next		= dir @ 'next'					# module next generation

.inc ../lex/readme
.inc ../lex/meta
.inc ../lex/win32rc

#cpp = next+file@'cpp.cpp'
#hpp = next+file@'hpp.hpp'

#.inc ../lex/tinymake

#.inc ../lex/parser
#.inc ../lex/lexer

files = [
	MODULE+'.bI' MODULE+'.blog'
	'../ypp.ypp' '../lpp.lpp' '../hpp.hpp' '../cpp.cpp' #'Makefile'
	'bat.bat' meta readme
]

.inc ../lex/bat
