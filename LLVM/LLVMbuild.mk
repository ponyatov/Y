LLVM_VER = 3.7.1
LLVM = llvm-$(LLVM_VER)
CLANG = cfe-$(LLVM_VER)
LLCRT = compiler-rt-$(LLVM_VER)
LLVM_GZ = $(LLVM).src.tar.xz
CLANG_GZ = $(CLANG).src.tar.xz
LLCRT_GZ = $(LLCRT).src.tar.xz

#SRC = /tmp/$(LLVM)
#BUILD = $(SRC)/build
GZ = $(HOME)/gz
TMP = /tmp/$(LLVM)
SRC = $(TMP)/src
BUILD = $(TMP)/build

DIRS = $(GZ) $(TMP) $(BUILD)

.PHONY: build
build:
	cd $(BUILD) && rm -rf $(BUILD)/* &&\
	../src/configure --enable-jit --prefix=$(HOME)/$(LLVM) --disable-docs \
		--enable-targets=host,x86,arm && make -j4
#gz dirs src

.PHONY: src
src:
	cd $(TMP) &&\
	xzcat $(GZ)/$(LLVM_GZ)  | tar x && mv -f $(LLVM).src $(SRC)
	cd $(SRC)/tools &&\
	xzcat $(GZ)/$(CLANG_GZ) | tar x && mv -f $(CLANG).src clang
	cd $(SRC)/projects &&\
	xzcat $(GZ)/$(LLCRT_GZ) | tar x && mv -f $(LLCRT).src compiler-rt

.PHONY: dirs
dirs:
	mkdir -p $(DIRS) && rm -rf $(BUILD)/*

.PHONY: gz
gz: $(LLVM_SRC)
WGET = wget -c -P $(GZ)
$(GZ)/$(LLVM_GZ): 
	$(WGET) http://llvm.org/releases/$(LLVM_VER)/$(LLVM_GZ)
$(GZ)/$(CLANG_GZ): 
	$(WGET) http://llvm.org/releases/$(LLVM_VER)/$(CLANG_GZ)
$(GZ)/$(LLCRT_GZ): 
	$(WGET) http://llvm.org/releases/$(LLVM_VER)/$(LLCRT_GZ)
