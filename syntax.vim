" Vim syntax file
" Language: bI
" Maintainer: Dmitry Ponyatov <dponyatov@gmail.com>
" GitHub: [https://github.com/ponyatov/Y/blob/dev/syntax.vim]

"if exists("b:current_"syntax")
"    finish
"endif

" comments
syntax match Comment "\v#.*"

" literals

" email
syntax match Constant "\v\<?[a-z]+\@[a-z\.]+\>?"
" url
syntax match Constant "\vhttps{0,1}://[a-zA-Z0-9\.\-\#\/]+"
" file
syntax match Constant "\v[a-zA-Z0-9\/]+\.[a-z]+"

" numbers
syntax match Number "\v0b[01]+"
syntax match Number "\v0x[0-9A-F]+"
syntax match Number "\v[\+\-]{0,1}[0-9]+"
syntax match Number "\v[\+\-]{0,1}[0-9]+\.[0-9]+"

" strings
syntax region String start="'" end="'"

" composite and classes
syntax match Function "\v\<[a-z]+:"

" code inlines
syntax match Keyword "\v\$"
syntax match Keyword "\v\?"

" dot-commands
syntax match Todo "\v\.[a-z]+\{?[ \t]*"

let b:current_syntax = "bI"

