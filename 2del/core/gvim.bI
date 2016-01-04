#.inc core/vim/filetype.bI
#.inc core/vim/syntax.bI

.file src.bat
\@rem $AUTOGEN$
\@start .
\@gvim -c "colorscheme $COLOR$" -p $FILES$
.eof

.file src.sh
\#!/bin/sh
gvim -c "colorscheme $COLOR$" -p $FILES$
.eof
