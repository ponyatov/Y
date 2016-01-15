# build: mingw32-make PFX=D:\LLVM dirs gz src cmake

LLVM_VER = 3.6.2

PFX = D:/LLVM

CMAKE_CFG = -DBUG_REPORT_URL=https://github.com/ponyatov/Y/tree/dev

LLVM_CMAKE_CFG = $(CMAKE_CFG) \
	-DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_INSTALL_PREFIX=$(PFX) \
	-DLLVM_EXTERNAL_MSBUILD_BUILD=OFF -DCMAKE_GNUtoMS=OFF \
	-DLLVM_INSTALL_TOOLCHAIN_ONLY=ON \
	-DBUILD_SHARED_LIBS=OFF \
	-DLLVM_TARGETS_TO_BUILD=host
#	-DLLVM_TARGETS_TO_BUILD=X86 -DLLVM_DEFAULT_TARGET_TRIPLE=i386-pc-mingw32

MINGW = C:/MinGW
XPATH = "$(MINGW)/bin;$(MINGW)/CMake/bin"

CMAKE_VER = 3.4.1
CMAKE = cmake-$(CMAKE_VER)

LLVM = llvm-$(LLVM_VER)
CLANG = cfe-$(LLVM_VER)
LLRT = compiler-rt-$(LLVM_VER)
LLVM_GZ = $(LLVM).src.tar.xz
CLANG_GZ = $(CLANG).src.tar.xz
LLRT_GZ = $(LLRT).src.tar.xz

TMP = D:/tmp/$(LLVM)
GZ = $(CURDIR)/gz
SRC = $(CURDIR)/src

DIRS = $(GZ) $(PFX) $(TMP) $(SRC)

.PHONY: dirs
dirs:
	mkdir -p $(DIRS)

.PHONY: gz
WGET = wget --no-check-certificate -c -P $(GZ)
gz: $(GZ)/$(CMAKE)-win32-x86.exe \
	$(GZ)/$(LLVM_GZ) $(GZ)/$(CLANG_GZ) $(GZ)/$(LLRT_GZ)
$(GZ)/$(CMAKE)-win32-x86.exe:
	$(WGET) https://cmake.org/files/v3.4/$(CMAKE)-win32-x86.exe
$(GZ)/$(LLVM_GZ):
	$(WGET) http://llvm.org/releases/$(LLVM_VER)/$(LLVM_GZ)
$(GZ)/$(CLANG_GZ):
	$(WGET) http://llvm.org/releases/$(LLVM_VER)/$(CLANG_GZ)
$(GZ)/$(LLRT_GZ):
	$(WGET) http://llvm.org/releases/$(LLVM_VER)/$(LLRT_GZ)

.PHONY: src
src: \
	$(SRC)/$(LLVM)/README \
	$(SRC)/$(LLVM)/tools/clang/README \
	$(SRC)/$(LLVM)/projects/compiler-rt/README

$(SRC)/$(LLVM)/tools/clang/README: $(GZ)/$(CLANG_GZ)
	cd $(SRC)/$(LLVM)/tools && rm -rf $(CLANG).src tools/clang &&\
	xzcat $< | tar x && mv $(CLANG).src tools/clang

#$(SRC)/$(LLVM)/README: $(GZ)/$(LLVM_GZ)  ############ xzcat symlink error
#	cd $(SRC) && rm -rf $(LLVM).src $(LLVM) &&\
#  	xzcat $< | tar x && mv $(LLVM).src $(LLVM) && touch $@

.PHONY: cmake
cmake: src
	rm -rf $(TMP)/* && $(MAKE) PATH=$(XPATH) cmake-cfg 
#	cmake-build
.PHONY: cmake-cfg
cmake-cfg:
	cd $(TMP) && cmake -G "MinGW Makefiles" $(LLVM_CMAKE_CFG) $(SRC)/$(LLVM)
.PHONY: cmake-build
cmake-build:
	cd $(TMP) && cmake --build .
cmake-install:
	cd $(TMP) && cmake --build . --target install
