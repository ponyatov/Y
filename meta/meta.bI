class:comment
comment @ 'this comment is object'
.end


TITLE = 'model'
ABOUT = 'bI language system metamodel'
LOGO = 'triangle'
COLOR = 'peachpuff'

.sec Files

next		= dir @ 'next'					# module next generation

.inc ../lex/readme
.inc ../lex/meta
.inc ../lex/win32rc

.inc ../lex/hpp
.inc ../lex/cpp
.inc ../lex/make

files = [
	bi log hpp cpp make
	'bat.bat'
#	MODULE+'.bI' MODULE+'.blog'
#	'../ypp.ypp' '../lpp.lpp' '../hpp.hpp' '../cpp.cpp' '../'+OS+'.cpp'
]

.inc ../lex/bat

