.title PROtotyping language system
.github https://github.com/ponyatov/pro

.file README.md
# ALYEH platform
## ALYEH:dYnamic language
### developer/experimental branch
Динамический язык программирования Ы (чтобы никто не догадался)

lisp in C(++): http://www.buildyourownlisp.com/contents
.eof

$() $(1234) $(56.78) $(-8e+9) $(xyz)
$(1+2) $(0x1234) $(0b1101)
$(	1+(2.3+someid)/query(http://ya.ru)	)
$(	1+2*-3-+4++							)

$(	1+2 3								)
$(	((1+2)/(3-4))						)

.file filetype.vim

.file syntax.vim

.file Makefile

.file cpp.cpp

.file hpp.hpp

.file ypp.ypp

.file lpp.lpp

.sec S-expressions inlining

$(	123 xyz 								)
$(	1+2 3									)
$(	((1+2)/(3-4))							)
$(	1+(2.3+someid)/query(http://ya.ru)		)
$(	1+2*-3-+4++								)

