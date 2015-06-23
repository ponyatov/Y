
.PHONY: go
go: Y.exe test.Y
	Y.exe < test.Y > test.log  

Y.exe: lex.yy.c
	$(CXX) $(CXXFLAGS) -o $@ $< 

lex.yy.c: Y.flex 
	flex Y.flex
 