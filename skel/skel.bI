
pp = { X: X+'pp' }
x.x = { X: pp@X+'.'+pp@X }
x.x@'y'

core		= x.x|[ 'y' 'l' 'h' 'c' ] + [ Makefile ]
files		= [ src.src log.log ] + core
bat.bat		= [ '@start .' '@gvim -p '+files/' ' ]
skeleton	= files + [ bat.bat .gitignore ]

pp
pp@'xx'

class:object
	%doc,'base metaclass'
	%init,{X}

