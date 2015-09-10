" Vim syntax file
" Language: bI
" Maintainer: Dmitry Ponyatov <dponyatov@gmail.com>
" GitHub: [https://github.com/ponyatov/Z/blob/master/syntax.vim]

"if exists("b:current_syntax")
"    finish
"endif


syntax region Comment start="#|" end="|#"
syntax match Comment "#.*$"

syntax match Keyword "\$[a-zA-Z0-9_]*"
syntax match Keyword "[\+\-=]"
syntax region Keyword start="\$(" end=")"

syntax match Constant "\\."
syntax match Constant "<tab>"

syntax match Identifier "\v[A-Z]+"
syntax match Constant "\v[a-zA-Z0-9]+\.[a-zA-Z0-9]+"
syntax match Constant "\vMakefile"

syntax match Todo "\v\.[a-z]+[^\n]*"
syntax region Todo start="\v\.[a-z]+[ \t]*\{" end="\}"

syntax match Keyword "\vclass.+"
syntax match Keyword "\v\@[a-z]+"
syntax match Keyword "\v\%[a-z]+"

syntax region String start="'" end="'"
syntax region String start="\"" end="\""

let b:current_syntax = "bI"

