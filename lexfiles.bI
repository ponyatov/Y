# lexical fileset skeleton

next		= dir @ MODULE					# module next generation

.inc ../Y/lex/readme.bI

files		= [
do			= next + file @ 'do.do'
log			= next + file @ 'log.log'
ypp			= next + file @ 'ypp.ypp'		"parser /bison/"
lpp			= next + file @ 'lpp.lpp'		"lexer /flex/"
hpp			= next + file @ 'hpp.hpp'		"c++ core headers"
cpp			= next + file @ 'cpp.cpp'		"c++ core code"
win32h		= next + file @ 'win32.hpp'
win32c		= next + file @ 'win32.cpp'
make		= next + file @ 'Makefile'
]

.inc ../Y/lex/gitignore.bI
.inc ../Y/lex/win32rc.bI
.inc ../Y/lex/bat.bI

