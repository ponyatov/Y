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

.sec \$ (dump) and \? (eval) prefixes

Code sections in bI script file must be marked using \$ and \? prefixes.

.sec- object dump

\$-prefixed code will be .term{dump}ed into symbol representation form of 
internal objects structure. \$ is sign of lisp S-expression with some bI 
specific extensions. Dumping can be used for debugging, and object 
serialization. Every bI object must include @dump writer method and @load 
constructor for serialization work.

.sec- object evaluation (computing)

\?-prefixed code will be computed using @eval methods in all nested objects.

.sec+ Data types

.sec Generics (primitive data types)

Generic bI language types provides highlevel abstracts for typical primitive
data types in other programming languages. Generics is gateway between machine
level types, and bI metaprogramming hell: it have all debug, profiling and 
tracking functions, but can be transparently transformed into primitive types
for statical compilation, native machine code or hardware synthesis.

.sec String

Most unversal data type, can represent and data in serialized form.

class String,str
	value
	@size		'size in chars'					-> int
	@+(str,str)	'concatenate'					-> str
	@*(str,int)	'repeat str num times'			-> str
	@*(str,str)	'fetch substrings using regexp'	-> list<str>
	@/(str,str)	'split str using regexp'		-> list<str>

'string1' # $'string2' ?'string3'

.sec Object

Generic object implements all bI-specific features for all other data types.

class Object
	str name	'class name'
	str value	'some textual value'
	@dump		'serializer/dumper'					-> '<'+cls+':'+val+'>'
	@load(str)	'deserialize constructor/loader'	-> %
	@eval		'evaluate (compute)'				-> % # as is

.sec Symbol

Any text string not detected as other literal, treated as symbol.
Symbol represents themself in dump, evaluation, and its value.

Object Symbol,sym
	lexer regexp = '[a-zA-Z_][a-zA-Z_0-9]+' # classical ID char set

$biClass $Symbol,$id
?biClass ?Symbol,?id

.sec- Number

Float and integer processing is too different, but Number type process both.

Object Number,num
	lexer regexp (
		S : '[\-\+]{0,1}'		# optional +/- sign
		D : '[0-9]+'			# decimal digits group
	)
	@dump -> %					# dump it as is
	@eval -> %					# eval it as is

Number Integer,int 
	lexer regexp (
		'{S}{D}'			# integers like -1 +2
		'0x[0-9A-F]+'		# hex literals
		'0b[01]+'			# bin literals
	)

Number Float,float
	lexer regexp (
		'{S}{D}\.{D}'		# dotted floats like -12.34
		'{S}{D}[eE]{S}{D}'	# exponential form -7e+8
	)	

$00 $-01 $+0002 
#$-3.4 $5.6 $+7.8 
#$-1e+3 $+4E-5

?00 ?-01 ?+0002 
#?-3.4 ?5.6 ?+7.8 
#?-1e+3 ?+4E-5


.sec Machine types

Machine types was inherited from LLVM design, and uses LLVM itself for code 
generation. 

.list
.li [iN]teger, N=2^n
.li [f]loat, [d]ouble
.li [v]ector

.sec Objects

.sec Containers (composite types)

