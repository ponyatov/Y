" Language: bI
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/Y
syntax match Comment	"\v#.*"						" # line comment
syntax match Todo		"\v^\.[a-z]+[\+\-]?[ \t]*"	" .directive
syntax match Keyword	"\v\$"						" $ inline expression
syntax match Keyword	"\v\?"						" ? inline expression
syntax match Constant	"\v[\+\-]?[0-9]+[eE][\+\-]?[0-9]+"	" num
syntax match Constant	"\v[0-9]+"							" int

" 'string'
syntax region	String		start="'" end="'"

" symbols
syntax match	Identifier		"\v\%[TFNE\%]"
syntax match	Special	"\v[a-zA-Z_]+"

" operators
syntax match	Type		"\v[\[\]\(\)\=]"

let b:current_syntax = "bI"
