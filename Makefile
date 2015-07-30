EXE ?= .exe

all: bI$(EXE)

bI$(EXE): flex.flex bison.bison cpp.cpp
	flex flex.flex
	bison bison.bison
	g++ -o $@ cpp.cpp

