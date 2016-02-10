TITLE = 'metamodel'
ABOUT = 'tiny language metamodel'
GITHUB = 'https://github.com/ponyatov/Y/tree/dev/'+MODULE+'/'
COLOR = 'peachpuff'
LOGO = 'warning'

next		= dir @ 'next'					# module next generation

.inc ../lex/readme
.inc ../lex/meta
.inc ../lex/win32rc

files = [
	
	'bat.bat' meta readme win32rc
]

.inc ../lex/bat
