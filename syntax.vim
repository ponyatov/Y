" Language: bI
" Maintainer: Dmitry Ponyatov <dponyatov@gmail.com>
" GitHub: [https://github.com/ponyatov/Y/blob/dev/syntax.vim]
" add to: $WINHOME/vimfiles/syntax/bI.vim: source D:\w\Y\syntax.vim

"if exists("b:current_"syntax")
"    finish
"endif

" line comments
syntax match	Comment		"\v#.*"

" directives 
syntax match	Todo		"\v^\.[a-z]+[ \t]*"
syntax region	Comment		start=".about{" end="}"

"" literals

" email
syntax match	Constant	"\v[a-z]+\@[a-z]+(\.[a-z]+)+"
" url
syntax match	Constant	"\vhttps?:\/\/[a-z]+(\.[a-z]+)+(\/[a-zA-Z_\.]+)+"
" file
syntax match	Constant	"\v[a-z\*\?]+(\.[a-z\*\?]+)+"

" strings
syntax region	String		start="'" end="'"

"" core language

" core class inheritance
syntax match	Keyword		"\v^class"
" core class fields and signals
syntax keyword	Function	regexp
" operators
syntax match	Keyword		"="

" numbers
"syntax match Number "\v0b[01]+"
"syntax match Number "\v0x[0-9A-F]+"
"syntax match Number "\v[\+\-]{0,1}[0-9]+"
"syntax match Number "\v[\+\-]{0,1}[0-9]+\.[0-9]+"

" composite and classes
"syntax match Function "\v[a-z]+:"

" code inlines
"syntax match Keyword "\v\$"
"syntax match Keyword "\v\?"
"syntax match Keyword "\v(class|lexer) "

"let b:current_syntax = "bI"

