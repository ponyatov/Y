" Language: bI
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/Y

" # line comments
syntax match	Comment		"\v#.*"

" .directive
syntax match	Todo		"\v^\.[a-z]+[\+\-]?[ \t]*"

" code inlines (X-expressions based on AST-like objects)
syntax match Keyword "\v\$"
syntax match Keyword "\v\@"
syntax match Keyword "\v\?"

" numbers
syntax match	Constant	"\v[0-9]+"

" 'string'
syntax region	String		start="'" end="'"

" symbols
syntax match	Todo		"\v\%[TFNE\%]"
syntax match	Keyword		"\v[a-zA-Z]+"

let b:current_syntax = "bI"
