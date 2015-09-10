au BufNewFile,BufRead *.bI set filetype=bI
" autload bI language budle files
au BufNewFile,BufRead *.bI tabf bI.log|set filetype=bI|set autoread
au BufNewFile,BufRead *.bI tabf syntax.vim|set filetype=vim
au BufNewFile,BufRead *.bI tabf bI.ypp|set filetype=yacc
au BufNewFile,BufRead *.bI tabf bI.lpp|set filetype=lex
au BufNewFile,BufRead *.bI tabf bI.cpp|set filetype=cpp
au BufNewFile,BufRead *.bI tabf bI.hpp|set filetype=cpp

au BufNewFile,BufRead *.bI tabf next/README.md|set filetype=text|set autoread
au BufNewFile,BufRead *.bI tabf next/Makefile|set filetype=make|set autoread
"au BufNewFile,BufRead *.bI tabf next/bI.ypp|set filetype=yacc|set autoread
"au BufNewFile,BufRead *.bI tabf next/bI.lpp|set filetype=lex|set autoread
"au BufNewFile,BufRead *.bI tabf next/bI.cpp|set filetype=cpp|set autoread
"au BufNewFile,BufRead *.bI tabf next/bI.hpp|set filetype=cpp|set autoread

au BufNewFile,BufRead *.bI tabf next/Object.cpp|set filetype=cpp|set autoread
au BufNewFile,BufRead *.bI tabf next/Object.hpp|set filetype=cpp|set autoread

au BufNewFile,BufRead *.bI tabn 1

au BufNewFile,BufRead *.bI set columns=99

" win32: copy to 
" $(HOME)/_vimrc
"nnoremap <F4> :w<CR>:!mingw32-make EXE=.exe clean<CR>
"inoremap <F4> <ESC>:w<CR>:!mingw32-make EXE=.exe clean<CR>
"inoremap <F5> <ESC>:syn off<CR>:syn on <CR><INS>
"nnoremap <F5> :syn off<CR>:syn on <CR>
" $(HOME)/vimfiles/ftdetect/bI.vim 
"nnoremap <F9> :w<CR>:!mingw32-make EXE=.exe upgrade<CR>
"inoremap <F9> <ESC>:w<CR>:!mingw32-make EXE=.exe upgrade<CR>

