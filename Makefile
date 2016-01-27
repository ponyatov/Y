## make parameters: OS=win32|linux EXE=.exe|.elf RES=res.res| TAIL=-n17|-n7
MODULE ?= $(notdir $(CURDIR))
.PHONY: exec
exec: ./$(MODULE)$(EXE) $(MODULE).bI
	./$(MODULE)$(EXE) < $(MODULE).bI > $(MODULE).blog && tail $(TAIL) $(MODULE).blog
C += ../Y/cpp.cpp ../Y/$(OS).cpp ypp.tab.cpp lex.yy.c
H += ../Y/hpp.hpp ../Y/$(OS).hpp ypp.tab.hpp meta.hpp
L += 
CXXFLAGS += -I../Y -I. -std=gnu++11 -DMODULE=\"$(MODULE)\" -DOS=\"$(OS)\"
./$(MODULE)$(EXE): $(C) $(H) $(RES) Makefile ../Y/Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(C) $(L) $(RES)
ypp.tab.cpp: ../Y/ypp.ypp
	bison $<
lex.yy.c: ../Y/lpp.lpp
	flex $<
res.res: rc.rc
	windres $< -O coff -o $@

.PHONY: clean
clean:
	rm -rf *.exe *.*log ypp.tab.?pp lex.yy.c res.res *~

