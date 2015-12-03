" Language: bI
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/Y
syntax match  Comment	"\v#.*"						" # line comment
syntax match  Todo		"\v\.[a-z]+[\+\-]?[ \t]*"	" .directive
syntax match  Keyword	"\v\$"						" $ inline expression
syntax match  Keyword	"\v\?"						" ? inline expression
syntax match  Type		"\v[\[\]\(\)\<\>\=\+\-\*\/]"	" operators & brackets
syntax match  Identifier "\v[\{\}]"						" lambda brackets
syntax match  Keyword	"\v\@"							" lambda apply
syntax match  Keyword	"\v\%"								" member of
syntax match  Type		"\v:"								" pair/typedef
syntax match  Constant	"\v[0-9]+[eE][\+\-]?[0-9]+"			" exponential
syntax match  Constant	"\v[0-9]+\.[0-9]+"					" float
syntax match  Constant	"\v[0-9]+"							" int
syntax region String	start="'" end="'"					" string
syntax region Comment	start="\"" end="\""					" docstring
"syntax match  Identifier "\v\%[TFNE\%]"						" special
syntax match  Special	"\v[a-zA-Z_]+"						" symbol
let b:current_syntax = "bI"
