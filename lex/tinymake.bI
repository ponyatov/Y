#bi	= next + file @ (MODULE+'.bI')
#log	= next + file @ (MODULE+'.blog')

exe = './'+MODULE+'.exe'

#cpp = next+file@'cpp.cpp'
#hpp = next+file@'hpp.hpp'

CFILES = [ cpp ]
HFILES = [ hpp meta.hpp ]

make = next + file @ 'Makefile'
make += 'MODULE = '+MODULE+'\n'
make += '.PHONY: exec\nexec: '+exe+'\n\t'+exe+'\n'
make += 'C = '+CFILES+'\n'
make += 'H = '+HFILES+'\n'
make += 'CXXFLAGS += -I. -std=gnu++11 -DMODULE="'+MODULE+'"\n'
make += exe+': $(C) $(H)\n\t$(CXX) $(CXXFLAGS) -o $@ $(C)\n'

