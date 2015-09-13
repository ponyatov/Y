" Vim syntax file
" Language: bI
" Maintainer: Dmitry Ponyatov <dponyatov@gmail.com>
" GitHub: [https://github.com/ponyatov/Y/blob/dev/syntax.vim]

"if exists("b:current_"syntax")
"    finish
"endif

syntax match Constant "\vhttp.+"

syntax match Keyword "\v\.[a-z]+"
syntax match Function "\v\$[a-zA-Z]+"
syntax match Function "[\+\-\*\/]"
syntax keyword Keyword module file url

syntax match Constant "\v[a-z]+\@[a-z\.]+"
syntax match Constant "\vhttps{0,1}://[a-z0-9\.\-\#\/]+"
syntax match Constant "\v[a-zA-Z]+\.[a-z]+|Makefile"

syntax match Todo "\v\$\("

syntax match Comment "\v#.*$"
syntax region Comment start="#|" end="|#"

"syntax match Keyword "\$[a-zA-Z0-9_]*"
"syntax match Keyword "[\+\-=]"
"syntax region Keyword start="\$(" end=")"

"syntax match Constant "\\."
"syntax match Constant "<tab>"

"syntax match Identifier "\v[A-Z]+"
"syntax match Constant "\v[a-zA-Z0-9]+\.[a-zA-Z0-9]+"
"syntax match Constant "\vMakefile"

"syntax match Todo "\v\.[a-z]+[^\n]*"
"syntax region Todo start="\v\.[a-z]+[ \t]*\{" end="\}"

"syntax match Keyword "\vclass.+"
"syntax match Keyword "\v\@[a-z]+"
"syntax match Keyword "\v\%[a-z]+"

"syntax region String start="'" end="'"
"syntax region String start="\"" end="\""

let b:current_syntax = "bI"

