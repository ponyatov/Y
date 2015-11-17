.file src.bat
\@rem $AUTOGEN$
\@start .
\@gvim -p $MODULE$.config $FILES$
.eof
.file src.sh
\#!/bin/sh
gvim -p $MODULE$.config $FILES$
.eof
