CXX=clang++

.PHONY: all
all: Y.exe  

Y.exe: lex.yy.c
	$(CXX) $(CXXFLAGS) -o $@ $< 

lex.yy.c: Y.flex 
	flex Y.flex
 