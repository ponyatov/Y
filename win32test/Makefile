MODULE = $(notdir $(CURDIR))
.PHONY: exec
exec: ./exe.exe
	./exe.exe
./exe.exe: cpp.cpp hpp.hpp
	$(CXX) -DMODULE=\"$(MODULE)\" -o $@ $<
