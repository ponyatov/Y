# lexical program module template
# uses sym/ template subtree

#.module PIL
#.title bI/PIL
#.about Program In Line
#.author (c) Jonh Doe <jd@mail.com>
#.github

.inc app/gitignore.pil
ST
.eof

.inc app/gvim.bI
.file filetype.vim
.file syntax.vim
.file ypp.ypp
.file lpp.lpp

.inc sym/hpp.pil

.file cpp.cpp
.inc makefile.pil # includes lexic makefile template
.inc app/readme.bI
