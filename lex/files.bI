# lexical fileset skeleton

next		= dir @ MODULE					# module next generation

.inc ../Y/lex/readme.bI
.inc ../Y/lex/gitignore.bI
.inc ../Y/lex/win32rc.bI

files = [
bi	= next + file @ (MODULE+'.bI')
log	= next + file @ (MODULE+'.blog')

.inc ../Y/lex/parser.bI
.inc ../Y/lex/lexer.bI
.inc ../Y/lex/headers.bI
.inc ../Y/lex/cpp.bI

]

exe = './'+MODULE+'.exe'
log = MODULE+'.blog'

CFILES = [ cpp '../../Y/'+OS+'.cpp' 'ypp.tab.cpp' 'lex.yy.c' ]/' '
HFILES = [ hpp '../../Y/'+OS+'.hpp' 'ypp.tab.cpp' ]/' '
.inc ../Y/lex/make.bI


.inc ../Y/lex/bat.bI


