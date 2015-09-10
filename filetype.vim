au BufNewFile,BufRead *.pro set filetype=pro
" autload bI language budle files
au BufNewFile,BufRead *.pro tabf log.log|set filetype=pro|set autoread
au BufNewFile,BufRead *.pro tabf syntax.vim|set filetype=vim
au BufNewFile,BufRead *.pro tabf ypp.ypp|set filetype=yacc
au BufNewFile,BufRead *.pro tabf lpp.lpp|set filetype=lex
au BufNewFile,BufRead *.pro tabf cpp.cpp|set filetype=cpp
au BufNewFile,BufRead *.pro tabf hpp.hpp|set filetype=cpp
au bufNewFile,BufRead *.pro tabf Makefile|set filetype=make

au BufNewFile,BufRead *.pro tabn 1

au BufNewFile,BufRead *.pro set columns=99

