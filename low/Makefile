CXX=clang++

.PHONY: all
all: Y.exe  

Y.exe: lex.yy.c 
	bison Y.bison
	exit -1
	$(CXX) $(CXXFLAGS) -o $@ $< 

lex.yy.c: Y.flex 
	flex Y.flex
 