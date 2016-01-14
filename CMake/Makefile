
MINGW = C:/MinGW
XPATH = "$(MINGW)/bin;$(MINGW)/CMake/bin"

.PHONY: cmake
cmake:
	mkdir -p build && rm -rf build/*
	$(MAKE) PATH=$(XPATH) cmake-cfg

.PHONY: cmake-cfg
cmake-cfg:
	cd build && cmake -G "MinGW Makefiles" ..
