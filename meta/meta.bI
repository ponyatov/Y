
TITLE = 'model'
ABOUT = 'bI language system metamodel'
LOGO = 'triangle'
COLOR = 'peachpuff'

next		= dir @ 'next'					# module next generation

.inc ../lex/readme
.inc ../lex/meta
.inc ../lex/win32rc

files = [
	readme meta win32rc 'bat.bat'
#	MODULE+'.bI' MODULE+'.blog'
#	'../ypp.ypp' '../lpp.lpp' '../hpp.hpp' '../cpp.cpp' '../'+OS+'.cpp'
]

.inc ../lex/bat
