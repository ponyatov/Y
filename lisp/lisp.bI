
TITLE = 'Lisp engine realization in bI'

next = dir @ MODULE

readme = next += file @ 'README.md'

readme += '# ' + MODULE +'\n'
readme += '### ' + TITLE + '\n'
readme += '\n' + AUTHOR +'\n'
readme += '\nlicence: '+LICENSE+ '\n'
readme += '\nGitHub: '+GITHUB+'/'+MODULE+'\n'

#[ 0 file 'ypp.ypp' ] "parser"
#[ dir 'next' ] "next generation dir"
#MODULE OS
#[ file 'ypp.ypp' ] "parser" 
#[ file 'lpp.lpp' ] "lexer"
#( file 'hpp.hpp' )
#( file 'cpp.cpp' )
#( file 'Makefile' )
#( file 'bat.bat' )
