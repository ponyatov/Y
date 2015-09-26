" Vim syntax file
" Language: bI/sym
" add to: $WINHOME/vimfiles/syntax/sym.vim: source D:\w\sym_stone\syntax.vim

" line comments
syntax match	Comment		"\v#.*"
" directives 
syntax match	Todo		"\v^\.[a-z]+[ \t]*\{?"
syntax region	Comment		start=".about{" end="}"
" email
syntax match	Constant	"\v[a-z]+\@[a-z]+(\.[a-z]+)+"
" url
syntax match	Constant	"\vhttps?:\/\/[a-z]+(\.[a-z]+)+(\/[a-zA-Z_\.]+)+"
" file
syntax match	Constant	"\v[a-z\*\?]+(\.[a-z\*\?]+)+"

"" core language
" tags part
syntax match	Function	"\v\<[a-z]+:"
syntax match	Keyword		"\v\<\@:"
" signal
syntax match	Function	"\v\@[a-z]+"
" core class inheritance
syntax keyword	Keyword		class
" string-defines symbols
syntax region	String		start="'" end="'"
" number symbols
syntax match	Number		"\v[0-9]+"

