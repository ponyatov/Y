MODULE = $(notdir $(CURDIR))
.PHONY: exec
exec: ./exe.exe
	./exe.exe
C = cpp.cpp
H = hpp.hpp
CXXFLAGS += -I. -std=gnu++11
#LIBS += -lgdi32
./exe.exe: $(C) $(H) $(RES) Makefile
	$(CXX) $(CXXFLAGS) -DMODULE=\"$(MODULE)\" -o $@ $(C) $(LIBS) $(RES)
res.res: rc.rc
	windres $< -O coff -o $@
