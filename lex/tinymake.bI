bi	= next + file @ (MODULE+'.bI')
log	= next + file @ (MODULE+'.blog')

exe = './'+MODULE+'.exe'

#cpp = next+file@'cpp.cpp'
#hpp = next+file@'hpp.hpp'

CFILES = [ cpp 'ypp.tab.cpp' 'lex.yy.c']/' '
HFILES = [ hpp 'ypp.tab.hpp' meta ]/' '

make = next + file @ 'Makefile'
make += 'MODULE = '+MODULE+'\n'
make += '.PHONY: exec\nexec: '+exe+'\n\t'+exe+' < '+bi+' > '+log
make += ' && tail $(TAIL) '+log+'\n'
make += 'C = '+CFILES+'\n'
make += 'H = '+HFILES+'\n'
make += 'CXXFLAGS += -I. -std=gnu++11 -DMODULE=\"'+MODULE+'\"\n'
make += exe+': $(C) $(H)\n\t$(CXX) $(CXXFLAGS) -o $@ $(C)\n'
make += 'ypp.tab.cpp: ypp.ypp\n\tbison $<\n'
make += 'lex.yy.c: lpp.lpp\n\tflex $<\n'

