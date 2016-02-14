" Language: bI
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/Y

au BufNewFile,BufRead *.bI		set filetype=bI
au BufNewFile,BufRead *.blog	set filetype=bI
au BufNewFile,BufRead *.blog	set autoread

au BufNewFile,BufRead src.src	set filetype=bI
au BufNewFile,BufRead log.log	set filetype=bI
au BufNewFile,BufRead log.log	set autoread

"au BufNewFile,BufRead *.ypp		set filetype=yacc
"au BufNewFile,BufRead *.lpp		set filetype=lex
"au BufNewFile,BufRead *.hpp		set filetype=cpp
"au BufNewFile,BufRead *.cpp		set filetype=cpp
"au BufNewFile,BufRead Makefile		set filetype=make
