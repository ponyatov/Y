MODULE = $(notdir $(CURDIR))
.PHONY: exec
exec: ./exe.exe
	./exe.exe
C = cpp.cpp
H = hpp.hpp
./exe.exe: $(C) $(H) Makefile
	$(CXX) -DMODULE=\"$(MODULE)\" -o $@ $(C)
