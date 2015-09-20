au BufNewFile,BufRead *.bI set filetype=bI
<<<<<<< HEAD
" autload bI language budle files
au BufNewFile,BufRead *.bI tabf bI.log|set filetype=bI|set autoread
au BufNewFile,BufRead *.bI tabf syntax.vim|set filetype=vim
au BufNewFile,BufRead *.bI tabf bI.ypp|set filetype=yacc
au BufNewFile,BufRead *.bI tabf bI.lpp|set filetype=lex
au BufNewFile,BufRead *.bI tabf bI.cpp|set filetype=cpp
au BufNewFile,BufRead *.bI tabf bI.hpp|set filetype=cpp
au bufNewFile,BufRead *.bI tabf Makefile|set filetype=make

au BufNewFile,BufRead *.bI tabn 1

au BufNewFile,BufRead *.bI set columns=99

=======
au BufNewFile,BufRead *.blog set filetype=blog

au BufNewFile,BufRead *.bI tabf bI.blog|set filetype=blog|set autoread
au BufNewFile,BufRead *.bI tabf syntax.vim|set filetype=vim
au BufNewFile,BufRead *.bI tabf parser.ypp|set filetype=yacc
au BufNewFile,BufRead *.bI tabf lexer.lpp|set filetype=lex
au BufNewFile,BufRead *.bI tabf bI.hpp|set filetype=cpp
au BufNewFile,BufRead *.bI tabf core.cpp|set filetype=cpp
"au bufNewFile,BufRead *.bI tabf Makefile|set filetype=make

au BufNewFile,BufRead *.bI tabn 1

>>>>>>> master
