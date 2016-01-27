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
bat			= next + file @ 'bat.bat'		"(g)vim helper"
win32rc		= next + file @ 'rc.rc'			"win32 resources"

.inc ../Y/lex/gitignore.bI

# bat

bat += '@start .\n'
bat += '@gvim -c "colorscheme peachpuff" -p '+files/' '+'\n'

# rc.rc
win32rc += 'logo ICON "../icons/'+LOGO+'.ico"\n'
