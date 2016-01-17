MODULE = $(notdir $(CURDIR))
.PHONY: exec
exec: ./exe.exe
	./exe.exe
C = cpp.cpp
H = hpp.hpp
#CXXFLAGS += -I. -std=gnu++11
./exe.exe: $(C) $(H) Makefile
	$(CXX) $(CXXFLAGS) -DMODULE=\"$(MODULE)\" -o $@ $(C)
