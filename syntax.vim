" Language: bI/sym
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, All rights reserved
" GitHub: https://github.com/ponyatov/YbI

" # line comments
syntax match	Comment		"\v#.*"

" .directive
syntax match	Todo		"\v^\.[a-z]+[\+\-]?[ \t]*"

" code inlines (X-expressions based on AST-like objects)
syntax match Keyword "\v\$"
syntax match Keyword "\v\@"

" number (not supported by bI language, only color highligh for easy reading)
syntax match	Constant	"\v[0-9]+"

" 'string'
syntax region	String		start="'" end="'"

" <object:dump>
syntax match	Constant	"\v\<.+\:.+\>"

let b:current_syntax = "bI"
