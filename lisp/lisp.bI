
TITLE
TITLE = 'Lisp engine realization in bI'
TITLE

next = dir @ MODULE

readme = next += file @ 'README.md'

readme += '# ' + MODULE +'\n'
readme += '### ' + TITLE + '\n'

TITLE

#[ 0 file 'ypp.ypp' ] "parser"
#[ dir 'next' ] "next generation dir"
#MODULE OS
#[ file 'ypp.ypp' ] "parser" 
#[ file 'lpp.lpp' ] "lexer"
#( file 'hpp.hpp' )
#( file 'cpp.cpp' )
#( file 'Makefile' )
#( file 'bat.bat' )
