au BufNewFile,BufRead *.sym set filetype=sym
au BufNewFile,BufRead *.sym tabf %:r.log|set filetype=sym|set autoread
au BufNewFile,BufRead *.sym tabf %:r.ypp|set filetype=yacc
au BufNewFile,BufRead *.sym tabf %:r.lpp|set filetype=lex
au BufNewFile,BufRead *.sym tabf %:r.hpp|set filetype=cpp
au BufNewFile,BufRead *.sym tabf %:r.cpp|set filetype=cpp
au BufNewFile,BufRead *.sym tabf Makefile|set filetype=make
au BufNewFile,BufRead *.sym tabn 1
