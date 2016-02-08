
TITLE = 'genmodule'
ABOUT = 'script generates lexical skeleton (see genmodule.bat)'
GITHUB = GITHUB+'/'+MODULE
COLOR = 'peachpuff'

next		= dir @ 'next'					# module next generation

.inc ../lex/readme
.inc ../lex/meta
.inc ../lex/win32rc
.inc ../lex/make

.inc ../lex/parser
.inc ../lex/lexer

files = [
	MODULE+'.bI' MODULE+'.blog'
	yacc lex 'hpp.hpp' 'cpp.cpp'
	make meta
]

.inc ../lex/bat
