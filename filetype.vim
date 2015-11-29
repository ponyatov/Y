" Language: bI
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/Y
au BufNewFile,BufRead *.bI  set filetype=bI
au BufNewFile,BufRead *.b	set filetype=bI
au BufNewFile,BufRead *.log   set filetype=bI
au BufNewFile,BufRead *.log   set autoread
au BufNewFile,BufRead *.blog  set filetype=bI
au BufNewFile,BufRead *.blog  set autoread
au BufNewFile,BufRead *.config set filetype=bI
au BufNewFile,BufRead *.ypp set autoread
au BufNewFile,BufRead *.ypp set filetype=yacc
au BufNewFile,BufRead *.lpp set autoread
au BufNewFile,BufRead *.lpp set filetype=lex
au BufNewFile,BufRead *.hpp set autoread
au BufNewFile,BufRead *.cpp set autoread
au BufNewFile,BufRead Makefile set autoread
