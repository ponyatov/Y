
TITLE	= '[Lo]w [L]evel Compiler'
ABOUT	= 'LLVM wrapper'
LOGO	= 'llvm'

.sec Files
next = dir @ 'next'
.inc ../lex/readme
.inc ../lex/meta
.inc ../lex/win32rc

.inc ../lex/hpp
.inc ../lex/cpp
.inc ../lex/make

files = [
	bi log
	hpp cpp
	make
	readme
	meta
	win32rc
	'bat.bat'
]
.inc ../lex/bat
