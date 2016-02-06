mkdir %1
cd %1
cp ../lex/genmodule.bI ./%1.bI
cp ../lex/meta.hpp ./
ls -la
mingw32-make -f ../Makefile EXE=.exe OS=win32
cd ..
