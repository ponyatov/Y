
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

" composite and classes
syntax match Function "\v\<[a-z]+:"

" dot-commands
syntax match Todo "\v\.[a-z]+\{?[ \t]*"

