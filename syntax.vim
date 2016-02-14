" Language: bI
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/Y

syntax match  Todo      "\v^\.[a-z]+[^\n]*"					" .directive
syntax match  Comment	"\v#.*"								" # line comment
syntax match  Comment	"\v\\_+"
syntax match  Comment	"\v\|\ +"

syntax match  Constant	"\v[\+\-]?[0-9]+L?"					" integer
syntax match  Constant	"\v[\+\-]?[0-9]+\.[0-9]+"			" floating point
syntax match  Constant	"\v[\+\-]?[0-9]+[eE][\+\-]?[0-9]+"	" exponential
syntax match  Constant	"\v0x[0-9A-F]+"						" hex
syntax match  Constant	"\v[0-9A-F]+[Hh]"
syntax match  Constant	"\v0b[01]+"							" bin
syntax match  Constant	"\v[01]+[Bb]"
syntax region String	start="'" end="'"					" 'string'
syntax region Special	start="\"" end="\""					" "docstring"

														" symbols not colored

syntax match  Keyword	"\v[+\-/]"							" operator
syntax match  Type		"\v[{}()[\]<>:=]"						" brackets
syntax match  Keyword	"\v[`@%]"							" lambda coloring

syntax match Constant	"\v<(MODULE|OS|LOGO|COLOR)>"
syntax match Constant	"\v<(TITLE|ABOUT|AUTHOR|GITHUB|LICENSE)>"
syntax match Constant	"\v<(doc|dir|file|str)>"
syntax match Function	"\v<(upcase)>"
syntax match Keyword	"\v(\.|nil)"
syntax match Todo		"\v^\.[a-z]+.*"

let b:current_syntax = "bI"
