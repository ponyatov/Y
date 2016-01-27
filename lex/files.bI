# lexical fileset skeleton

next		= dir @ MODULE					# module next generation

.inc ../Y/lex/readme.bI
.inc ../Y/lex/gitignore.bI
.inc ../Y/lex/win32rc.bI

files = [
bi	= next + file @ (MODULE+'.bI')
log	= next + file @ (MODULE+'.blog')
]

.inc ../Y/lex/bat.bI

