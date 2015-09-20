<<<<<<< HEAD

.title		ALYEH platform
.subtitle	dYnamic language bI
.author		Dmitry Ponyatov <dponyatov@gmail.com>
.github		https://github.com/ponyatov/pro

.about		{

\#\#\# bibliography

* lisp in C(++): http://www.buildyourownlisp.com/contents
* SICP
* Dragon Book: Aho Seti Ulmann Compilers. Principles and technology

\#\#\# required tools:

* MinGW [http://www.mingw.org/] GNU CC toolchain for win32
* GnuWin32 http://gnuwin32.sourceforge.net/packages.html
* git-scm [https://git-scm.com/] GitHub client for project versioning
* (g)Vim 7.4 [http://www.vim.org/download.php#pc] power code editor

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

$(A B C)

<end>

$()$ $(1234)$ $(56.78)$ $(-8e+9)$ $(xyz)$
$(1+2)$ $(0x1234)$ $(0b1101)$
$(	((1+2)/(3-4))						)$
$(	1+(2.3+someid), query(http://ya.ru)	)$
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

	| Sexpr SPACE			{ $$=$1; }
	| SPACE Sexpr			{ $$=$2; }

	| EOL					{ $$=$1; }
	| spaces SPACE 			{ $$=$2; }
	| spaces EOL			{ $$=$2; }

spaces : 
	  SPACE 				{ $$=$1; }
;
	
.sec Intel Xeon X5560 code generation & optmimization

Cluster "Sergey Korolev" http://hpc.ssau.ru/ :
* CPU: 2x Intel Xeon X5560, 2.80GHz, 8MB Cache;
* Memory: 12 GB;

.sec Out-of-order execution

.sec LLVM tuned backend
=======
#!/Y

.title		bI dynamic language system
.author		Dmitry Ponyatov <dponyatov@gmail.com>
.github		https://github.com/ponyatov/Y

.sec Goal

.list The goal of bI language design is 
.li ultra high level scripting, programming and design system, supports
.li dynamic metaprogramming on large computers, 
.li statical cross-compilation for tiny embedded systems,
.li hardware design including CAD/CAM/CAE/EDA functions,
.li science data crunching and visualization and
.li text data processing including translation and compilers design.

.sec Literate programming

Documentation is program, program must be selfdocumented.

.sec Free Syntax Programming

Language syntax is under your control, bI it mutable DSL for your own tasks.

.sec Composition

bI is composite language, mix of OOP, functional, literate programming,...,
and all modern programming languages.

.sec Bootstrapping

Core language system written in flex, bison and C++, 
bI/next (next generation) is realized in bI themself.

.sec+ Core syntax

.sec Bypass translation

All undetected text data must be bypassed from stdin to stdout.
Data detected as language constructs will be computed inplace.

.sec Directives

Directives is documentation markup mainly, 
but can control bI system in other way.

biClass Directive lexer regexp = '\.[a-z]+'

.sec \ escape char

\ escape char is prefix before any special char marks use this char as is.

.sec Comments

Comments must be removed from output.
# line comments until end of line 

biClass LineComment lexer regexp = '\#.*\n'

.sec $ (dump) and ? (eval) prefixes

Code sections in bI script file must be marked using $ and ? prefixes.

.sec- object dump

$-prefixed code will be .term{dump}ed into symbol representation form of 
internal objects structure. $ is sign of lisp S-expression with some bI specific 
extensions. Dumping can be used for debugging, and object serialization.
Every bI object must include @dump writer method and @load constructor for 
serialization work.

.sec- object evaluation (computing)

?-prefixed code will be computed using @eval methods in all nested objects.

.sec+ Data types

.sec Generics (primitive data types)

Generic bI language types provides highlevel abstracts for typical primitive
data types in other programming languages. Generics is gateway between machine
level types, and bI metaprogramming hell: it have all debug, profiling and 
tracking functions, but can be transparently transformed into primitive types
for statical compilation, native machine code or hardware synthesis.

.sec Symbol

Any text string not detected as other literal, treated as symbol.
Symbol represents themself in dump, evaluation, and it's value.

biClass Symbol,ID
	lexer regexp = '[a-zA-Z_][a-zA-Z_0-9]+' # classical ID char set
	@dump -> %								# dump it as is
	@eval -> %								# eval it as is

.sec- 

.sec Machine types

Machine types was inherited from LLVM design, and uses LLVM itself for code 
generation. 

.list
.li [iN]teger, N=2^n
.li [f]loat, [d]ouble
.li [v]ector

.sec Objects

.sec Containers (composite types)
>>>>>>> master

