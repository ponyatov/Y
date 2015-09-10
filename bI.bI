
.title		ALYEH:dYnamic language
.subtitle	Динамический язык программирования Ы (чтобы никто не догадался)
.author		Dmitry Ponyatov <dponyatov@gmail.com>
.github		https://github.com/ponyatov/pro
.about		{

Used manual: lisp in C(++): http://www.buildyourownlisp.com/contents

\#\#\# required tools:

* MinGW [http://www.mingw.org/] GNU CC toolchain for win32
* GnuWin32 http://gnuwin32.sourceforge.net/packages.html
* git-scm [https://git-scm.com/] GitHub client for project versioning
* (g)Vim 7.4 [http://www.vim.org/download.php#pc] power programming editor

\#\#\# current state:

* win32 only (minimal linux)
* no manuals, short comments badENglish only
* no JIT compiling and optimization, pure interpreter

}

.file README.md
\# ALYEH platform
\#\# $TITLE
\#\#\# $SUBTITLE
developer/experimental branch

(c) $AUTHOR 

$ABOUT

depends on: $DEPENDS
.eof

.sec S-expressions inlining

$()$ $(1234)$ $(56.78)$ $(-8e+9)$ $(xyz)$
$(1+2)$ $(0x1234)$ $(0b1101)$
$(	((1+2)/(3-4))						)$
$(	1+(2.3+someid)/query(http://ya.ru)	)$
$(	1+2*-3-+4++							)$
#$(	1+2 3								)$

.file filetype.vim

.file syntax.vim

.file Makefile

.sec Language runtime system

.sec Lexer
.file lpp.lpp

.sec Parser
.file ypp.ypp

.sec Runtime

.file cpp.cpp

.file hpp.hpp


.sec Core object system

bI object systems based on SmallTalk-like fully dynamic objects, messaging 
system and inheri-by-copy approach.

class Object

class Object
	%super	"super objects list"
	%child	'inherited objects list'
	@new	'constructor'
	@del	'destructor/finalizer'
	@dump	'dump object into string representation'
	@copy	'copy constructor'
	@inher	'inheriatance via object copy: super creates inherited class'

.sec Comments

class Comment: Object

class LineComment: Comment

# this is line comment

class BlockComment: Comment

#| this is 
	block 
		comment |#

.sec Scalar types

Scalar data types realized in native types, and covered by C++ compiler runtime.

.sec Native types

Current bI implementation uses only native scalar types, $next will use
platform-independent scalars with run-time tracking (on test suites) and
transforming into native types supported by LLVM.

struct biNative {
	enum  {INT,FLOAT,BIN,HEX,STR,PTR,FFILE} t;
	union {
		int i;
		float f;
		string *s;
		void *p;
		FILE *ff;
	} v;
};

.sec Integer

class Integer



.sec Literals

.sec Makefile
.file Makefile
\# $CHEADER

.PHONY: next
next: ./bI\$(EXE)

$MAKECPP
$MAKEHPP

./bI\$(EXE): \$(CPP) \$(HPP)
<tab>\$(CXX) \$(CXXFLAGS) -o \$@ \$(CPP)
lex.yy.c: $LEXER
<tab>flex $LEXER
bI.tab.cpp: $PARSER
<tab>bison -d $PARSER

$MAKE
