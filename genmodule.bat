mkdir %1
cd %1
cp ../lex/genmodule.bI ./%1.bI
cp ../lex/meta.hpp ./
ls -la
echo include ../Makefile > Makefile
mingw32-make EXE=.exe OS=win32
mv next/* ./
cd ..
