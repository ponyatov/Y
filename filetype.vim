au BufNewFile,BufRead *.bI set filetype=bI
au BufNewFile,BufRead *.bIog set filetype=bIog
" autload bI language budle files
au BufNewFile,BufRead *.bI tabf %:r.bIog|set filetype=bIog|set autoread
au BufNewFile,BufRead *.bI tabf %:r.toc|set filetype=config|set autoread
"au BufNewFile,BufRead *.bI tabf bI.tex|set filetype=tex|set autoread
au BufNewFile,BufRead *.bI tabf syntax.vim|set filetype=vim
au BufNewFile,BufRead *.bI tabf parser.ypp|set filetype=yacc
au BufNewFile,BufRead *.bI tabf %:r.ypp|set filetype=yacc
au BufNewFile,BufRead *.bI tabf lexer.lpp|set filetype=lex
au BufNewFile,BufRead *.bI tabf %:r.lpp|set filetype=lex
au BufNewFile,BufRead *.bI tabf bI.hpp|set filetype=cpp
au BufNewFile,BufRead *.bI tabf %:r.hpp|set filetype=cpp
au BufNewFile,BufRead *.bI tabf core.cpp|set filetype=cpp
au BufNewFile,BufRead *.bI tabf %:r.cpp|set filetype=cpp
"au bufNewFile,BufRead *.bI tabf Makefile|set filetype=make

au BufNewFile,BufRead *.bI tabn 1


