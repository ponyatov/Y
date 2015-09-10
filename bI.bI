.title PROtotyping language system
.github https://github.com/ponyatov/pro

.file README.md
\# pro
# this is line comment
PROtotyping system

.file filetype.vim

.file syntax.vim

.file Makefile

.file cpp.cpp

.file hpp.hpp

.file ypp.ypp

.file lpp.lpp

.sec S-expressions inlining

$() $(1234) $(56.78) $(-8e+9) $(xyz)
$(	123 xyz 								)
$(	1+2 3									)
$(	((1+2)/(3-4))							)
$(	1+(2.3+someid)/query(http://ya.ru)		)
$(	1+2*-3-+4++								)

