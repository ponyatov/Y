bi	= next + file @ (MODULE+'.bI')
log	= next + file @ (MODULE+'.blog')

exe = './'+MODULE+'.exe'

CFILES = [ cpp 'ypp.tab.cpp' 'lex.yy.c' ]/' ' # '../../'+OS+'.cpp' 
HFILES = [ hpp 'ypp.tab.hpp' 'meta.hpp' ]/' ' # '../../'+OS+'.hpp'   ]/' '

make = next + file @ 'Makefile'
make += 'MODULE = '+MODULE+'\n'
make += '.PHONY: exec\nexec: '+exe+' '+bi+'\n\t'+exe+' < '+bi+' > '+log+'\n'
make += 'C = '+CFILES+'\n'
make += 'H = '+HFILES+'\n'
make += 'CXXFLAGS += -I. -std=gnu++11 -DMODULE="\\"'+MODULE+'\\"" -DOS="'+OS+'"\n'
make += exe+': $(C) $(H)\n\t$(CXX) $(CXXFLAGS) -o $@ $(C)\n'
make += 'ypp.tab.cpp: ypp.ypp\n\tbison $<\n'
make += 'lex.yy.c: lpp.lpp\n\tflex $<\n'
#make += 'res.res: rc.rc\n\twindres $< -O coff -o $@\n'

make += '
.PHONY: upgrade
upgrade:
#	cp next/Makefile ./
	cp next/README.md ./
	cp next/meta.hpp ./
'
