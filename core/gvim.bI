.file src.bat
\@rem $AUTOGEN$
\@start .
\@gvim -c "colorscheme $COLOR$" -p $MODULE$.bI $MODULE$.blog $FILES$
.eof
.file src.sh
\#!/bin/sh
gvim -c "colorscheme $COLOR$" -p $MODULE$.bI $MODULE$.blog $FILES$
.eof
