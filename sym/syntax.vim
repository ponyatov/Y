" Language: bI/sym
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/Y/tree/dev/sym

" line comments
syntax match	Comment		"\v#.*"

" directives 
syntax match	Todo		"\v^\.[a-z]+[\+\-]?[ \t]*"

"" literals

" numbers
syntax match	Constant	"\v[0-9]+"

" strings
syntax region	String		start="'" end="'"
syntax region	String		start="\"" end="\""

" code inlines
syntax match Keyword "\v\$"
syntax match Keyword "\v\@"

"let b:current_syntax = "sym"

