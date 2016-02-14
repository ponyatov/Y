
TITLE = 'LLVM shell'
ABOUT = 'tiny LLVM assembly-like script'
GITHUB = GITHUB+'/'+MODULE
LOGO = 'triangle'
COLOR = 'peachpuff'

next		= dir @ 'next'					# module next generation

.inc ../lex/readme
.inc ../lex/meta
.inc ../lex/win32rc

.inc ../lex/parser
.inc ../lex/lexer
.inc ../lex/headers
.inc ../lex/cpp

.inc ../lex/make

files = [
	MODULE+'.bI' MODULE+'.blog'
	yacc lex hpp cpp
	make meta
]

.inc ../lex/bat
