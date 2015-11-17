.file src.bat
\@rem $AUTOGEN$
\@start .
\@gvim -p $FILES$
.eof
.file src.sh
\#!/bin/sh
gvim -p $FILES$
.eof
