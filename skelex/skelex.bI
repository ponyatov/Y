
bi	 = MODULE + '.bI'
blog = MODULE + '.blog'

.inc make

skelex = [
	files = [
		bi blog
		ypp.ypp lpp.lpp hpp.hpp cpp.cpp ~Makefile
	]
	bat = file@bat.bat
	.gitignore = [ '*~' '*.swp' exe blog 'ypp.tab.?pp' lex.yy.c ]
]

bat
+= '@start .'
+= 'gvim -p '+files/' '

hpp.hpp = [
	[ '#ifndef _H_'+upcase@MODULE '#define _H_'+upcase@MODULE ]
	[ '#endif // _H_'+upcase@MODULE ]
]

x.x
x.x = { EX: [ EX . EX ] }
x.x
x.x@y
x.x
