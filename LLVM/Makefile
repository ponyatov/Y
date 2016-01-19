MODULE = $(notdir $(CURDIR))
CXX = clang++
#OS = $(shell $(CXX) -dumpmachine)
OS = $(shell uname)
LLCXX = $(shell llvm-config --cxxflags)
LLLD = $(shell llvm-config --ldflags)
LLLIBS = $(shell llvm-config --libs bitwriter core support) -lpthread -ldl -lcurses
.PHONY: test
test: ./$(MODULE) test.llsh ll.S
	./$(MODULE) < $@.llsh > $@.log && tail $(TAIL) $@.log && make $(MODULE).ll 
#	 && make $(MODULE).ll
C = $(MODULE).cpp $(OS).cpp $(MODULE).parser.cpp $(MODULE).lexer.cpp
H = $(MODULE).hpp $(OS).hpp $(MODULE).parser.hpp
CXXFLAGS = -I. -DMODULE=\"$(MODULE)\" $(LLCXX) $(LLLD) -Wno-deprecated-register
./$(MODULE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C) $(LLLIBS)
$(MODULE).lexer.cpp: $(MODULE).lex
	flex -o $@ $<
$(MODULE).parser.cpp: $(MODULE).yacc
	bison -o $@ $<
	
ll.S: ll.ll
	clang -target i386-pc-none-elf -S -c -o $@ $<
	
c80.a80: c80.c80
	./scc8080 -t $< > $@
	
%.ll: %.bc
	llvm-dis -o $@ $< && tail $@