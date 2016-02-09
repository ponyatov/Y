mkdir -p %1
cd %1
cp ../lex/genmodule.bI ./%1.bI
cp ../lex/meta.hpp ./
echo include ../Makefile > Makefile
ls -la
mingw32-make EXE=.exe OS=win32
mv next/* ./
cd ..
