.file filetype.vim
" Language: bI
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/Y
au BufNewFile,BufRead *.bI  set filetype=bI
au BufNewFile,BufRead *.log   set filetype=bI
au BufNewFile,BufRead *.log   set autoread
au BufNewFile,BufRead *.blog  set filetype=bI
au BufNewFile,BufRead *.blog  set autoread
au BufNewFile,BufRead *.config set filetype=bI
au BufNewFile,BufRead *.ypp set autoread
au BufNewFile,BufRead *.lpp set autoread
au BufNewFile,BufRead *.hpp set autoread
au BufNewFile,BufRead *.cpp set autoread
au BufNewFile,BufRead Makefile set autoread
.eof

.file syntax.vim
" Language: bI
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/Y
syntax match  Comment	"\\v\#.*"						" \# line comment
syntax match  Todo		"\\v^\\.[a-z]+[\\+\\-]\?[ \\t]*"	" .directive
syntax match  Keyword	"\\v\\\$"						" \$ inline expression
syntax match  Keyword	"\\v\\\?"						" \? inline expression
syntax match  Type		"\\v[\\[\\]\\(\\)\\<\\>\\=\\+\\-\\*\\/]"		" operator
syntax match  Constant	"\\v[0-9]+[eE][\\+\\-]\?[0-9]+"			" exponential
syntax match  Constant	"\\v[0-9]+\\.[0-9]+"					" float
syntax match  Constant	"\\v[0-9]+"							" int
syntax region String	start="'" end="'"					" string
syntax match  Identifier "\\v\\%[TFNE\\%]"						" special
syntax match  Special	"\\v[a-zA-Z_]+"						" symbol
let b:current_syntax = "bI"
.eof

.file src.bat
\@rem $AUTOGEN$
\@start .
\@gvim -c "colorscheme $COLOR$" -p $FILES$
.eof
.file src.sh
\#!/bin/sh
gvim -c "colorscheme $COLOR$" -p $FILES$
.eof


