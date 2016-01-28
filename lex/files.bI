# lexical fileset skeleton

next		= dir @ 'next'					# module next generation

.inc ../lex/readme.bI
.inc ../lex/gitignore.bI
.inc ../lex/meta.bI
.inc ../lex/win32rc.bI

.inc ../lex/parser.bI
.inc ../lex/lexer.bI
.inc ../lex/headers.bI
.inc ../lex/cpp.bI

.inc ../lex/make.bI

files = [
	bi log
	yacc lex hpp cpp
	make
	'bat.bat'
]

.inc ../lex/bat.bI

