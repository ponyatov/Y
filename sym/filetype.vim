" Vim filetype file
" Language: bI/sym
" add to: $WINHOME/vimfiles/ftdetect/sym.vim: source D:\w\sym_stone\filetype.vim

au BufNewFile,BufRead sym.sym set filetype=sym
au BufNewFile,BufRead sym.log set filetype=sym

au BufNewFile,BufRead sym.sym tabf sym.log|set filetype=sym|set autoread

au BufNewFile,BufRead sym.sym tabf syntax.vim|set filetype=vim
au BufNewFile,BufRead sym.sym tabf sym.ypp|set filetype=yacc
au BufNewFile,BufRead sym.sym tabf sym.lpp|set filetype=lex
au BufNewFile,BufRead sym.sym tabf sym.hpp|set filetype=cpp
au BufNewFile,BufRead sym.sym tabf sym.cpp|set filetype=cpp
au BufNewFile,BufRead sym.sym tabf Makefile|set filetype=make

au BufNewFile,BufRead sym.sym tabn 1

