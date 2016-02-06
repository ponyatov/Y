
TITLE = 'genmodule'
ABOUT = 'script generates lexical skeleton (see genmodule.bat)'

next		= dir @ 'next'					# module next generation

.inc ../lex/readme
.inc ../lex/meta
.inc ../lex/win32rc

files = [
	MODULE+'.bI' MODULE+'.blog'
	'../ypp.ypp' '../lpp.lpp' '../hpp.hpp' '../cpp.cpp' '../'+OS+'.cpp'
]

.inc ../lex/bat
