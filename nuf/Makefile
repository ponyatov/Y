
.PHONY: nuf
nuf: ./nuf$(EXE)
	mkdir -p nuf
	./nuf$(EXE) < Makefile.nuf > nuf/Makefile
	./nuf$(EXE) < nuf.ypp.nuf > nuf/nuf.ypp
	./nuf$(EXE) < nuf.lpp.nuf > nuf/nuf.lpp
	./nuf$(EXE) < nuf.hpp.nuf > nuf/nuf.hpp
	./nuf$(EXE) < nuf.cpp.nuf > nuf/nuf.cpp

.PHONY: upgrade
upgrade: Makefile nuf.ypp nuf.hpp nuf.hpp nuf.cpp
	cp nuf/Makefile Makefile
	cp nuf/nuf.ypp nuf.ypp
	cp nuf/nuf.lpp nuf.lpp
	cp nuf/nuf.hpp nuf.hpp
	cp nuf/nuf.cpp nuf.cpp

.PHONY: clean
clean:
	rm -rf nuf

C = nuf.cpp lex.yy.c nuf.tab.cpp
H = nuf.hpp nuf.tab.hpp
./nuf$(EXE): $(C) $(H)
	$(CXX) $(CXXFLAGS) -o $@ $(C)
lex.yy.c: nuf.lpp
	flex $<
nuf.tab.cpp: nuf.ypp
	bison $<

