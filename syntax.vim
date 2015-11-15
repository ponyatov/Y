" Language: bI/PIL
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/PIL

syntax match	Comment		"\v#.*"
syntax match	Constant	"\v[0-9]+"
syntax match	Todo		"\v\%[TFNE\%]"
syntax match	Keyword		"\v[a-zA-Z]+"
syntax region	String		start="'" end="'"
