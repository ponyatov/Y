MODULE = dura

exec: ./$(MODULE)$(EXE)
	./$(MODULE)$(EXE) < $(MODULE).lex > $(MODULE).out
	
C = $(MODULE).cpp lex.yy.c $(MODULE).tab.cpp
H = $(MODULE).hpp $(MODULE).tab.hpp

./$(MODULE)$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
lex.yy.c: $(MODULE).lpp
	flex $<
$(MODULE).tab.cpp: $(MODULE).ypp
	bison $<

