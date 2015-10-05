C = pure.cpp lex.yy.c pure.tab.cpp
H = pure.hpp pure.tab.hpp
./pure.exe: $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
lex.yy.c: pure.lpp
	flex $<
pure.tab.cpp: pure.ypp
	bison $<
