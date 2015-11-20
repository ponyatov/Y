# dynamic class description

.module	minimal
.title	Minimal bI Program
.color	darkblue
.file minimal.config
.inc app/config.bI
.file minimal.blog
.inc app/readme.bI
#.inc readme.bI
.eof
.inc app/ypp.bI
.inc app/lpp.bI
.inc app/hpp.bI
.inc app/cpp.bI
.inc app/makefile.bI
.inc app/res.bI
.inc app/gvim.bI
.end

.inc app/config.bI
#fsdfds
.end

$main = 'int main() {}'
.inc minimal_program.bI
.end

.module ST
.title	SmallTalk-inspired object engine
.about	some experiments with OOP based on dynamic objects
.color darkblue
.inc gen_program.bI
.end

# [dana] test suite

# p.18
? [235.4 [2e10 2/3] "Hello, there!" <1 4.5 -7> . foobar]

#.end

# p.17
? [235.4 [2e10 2/3] "Hello, there!" <1 4.5 -7>]
? [foo [bar [[baz]] asdf] x:keyword]

# p.16
# numbers
? -1234 235.4 2e10 0x16 0b1101 # integer number number hex bin 
# symbols
? foo 2nd-place *foo
# specials
? %T %F %N %E # true false nil error
# strings
? "Str" 'ings'
# vectors (arrays)
? <1 "foo" A> <<A B C> <1 2 3>>
# structores
? <person first-name:dana last-name:nau>

# p.15
? [ + 2 3 5 ]		# (1)
? 5					# (2)
? [print [+ 2 3 5]]	# (3)
? [exit]			# (4)

# lexical program module template (PIL itself bootstrapping)
.module bI
.title bI/PIL
.about Program In Line
.inc lex_program.bI

.sec+	core language elements

.sec-	comments
# bI has line comment : required for UNIX script file header '#!/bin/sh'

.sec	source files

Source files is plain text with inlined bI expresssions, marked with:
\$ expression \$	evaluate and put calculated object string:value inline
\? expression \?	dump parsed input as AST syntax tree and calculated object

Paired markers and ignoring all spaces (including end of line)
gives multiline expression syntax.

bI system parses all data from stdin, bypass all undetected chars as-is into
stdout, but processes inlined expressions.

Use \.inc directive for including other source files.

.sec-	modules

\.module directive creates module: separate subdirectory, will be used for 
\.file creation.

Every module has some metadata controls module processing 
in code and documentation generation, and builded software deployment.

.sec-	files

If some text marked with .file .eof pair, all stdout data will be copied into
selected file. If .eof omitted, file will be closed until nest .file .eof 
or .module.

.sec	directives

All directives starts with .dot at first line position.

Directives used for source files markup, control bI system work,
define files and modules,...

.list Directives
.li \.sec \.sec+ \.sec-			doc	sectioning
.li \.list \.li					doc	lists
.li \.module \.file \.eof		src	define module and files in current module
.li \.title \.about \.author	src set module parameters
.li \.license \.github			src
.li \.color 					src set (g)vim colorsheme for generated module
.li \.inc						src include other source file

.sec	scalar data types
# bI language supports int/float numbers, symbols, strings, <vectors> and lists
? [ 1299999999999999993 04.5 [ -06e+77 some_sym]
[] [quit=exit] 'string' [0x12AFFFFFFFFFFFF 0b1101] [%T %F %N %E %%] ] ?

? < -01 [] 002 [[ +003 0x12AF ] 0b1101 ['this' is a 'string']]
  +04.5 +006e-07 > ?

# special symbols: true false nil error default
? [ [ %T %F ] %N %E %% ] ?

.sec	aggregate data types
# compound data types: [list] pa:ir nested=item <vector>
?[ list [] ='can be':empty nested=item <x y z> ]?

# = operator can be used for assigning values
?TITLE = '[minimal] Minimal bI Program' = xxx
	= ( '= supports multiple assignment' = 'left associativity' )?

# multiple assignment can be used for constructing complex objects
?form:About
	= ( Title = 'About ' + MODULE )
	= ABOUT
	= ( Buttons 
		= button:OK 
		= button:UPDATE 
	)?

# special symbols: true false nil error
? %T %F %N %E
# numbers, symbols, lists and strings
? -01 [] 002 [[ +003 0x12AF ] 0b1101 ['this' is a 'string']]
? +04.5 +006e-07
# comment

.end

.sec- Variables

pi=999		?pi=999		$pi=999		
pi			?pi			$pi
si=999		?si=999		$si=999		
si			?si		$si

sym $sym ?sym 

.sec- Science constants

bI has some constants:

pi		?pi		$pi		# Pi
e		?e		$e		# e
c		?c		$c		# light speed
G		?G		$G		# gravity const
g		?g		$g		# gravitational acceleration
h		?h		$h		# Plank constant

.end

.sec- Standart math functions

(1)
sin (1)
cos pi
tan ()

.sec Class construction

class Symbol	'core class'

Symbol Number	'any number'

.tocline

.sec+ Core syntax

.sec Bypass translation

All undetected text data must be bypassed from stdin to stdout.
Data detected as language constructs will be computed inplace.

Code sections in bI script file must be marked using \$ and \? prefixes.

.sec- \$ object dump

\$-prefixed code will be .term{dump}ed into symbol representation form of
internal objects structure. \$ is sign of lisp S-expression with some bI
specific extensions. Dumping can be used for debugging, and object
serialization. Every bI object must include @dump writer method and @load
constructor for serialization work.

.sec- \? object evaluation (computing)

\?-prefixed code will be computed using @eval methods in all nested objects.

.sec- inline constructs

Some syntax constructs works without and special marks,
but must be formatted properly for its detection, class definition for example.

For best markup and syntax undestanding you should use bI system
itself source code in bI.bI file. Use (g)vim and includes syntax files for
apropriate coloring highlighting.

.sec- \\ escape char

\\ escape char is prefix before any special char marks use this char as is.

.sec Comments

Comments must be removed from output.
# line comments until end of line

class Comment

class LineComment:Comment	regexp = '#[^\\n]*\\n'

.sec Infix expressions

15/7		?15/7		$15/7
1+15/7		?1+15/7		$1+15/7

1+2			?1+2		$1+2
2/3			?2/3		$2/3
1+2/3		?1+2/3		$1+2/3

.sec Directives

Elements starting with . is directives, they are for documentation markup 
mainly, but can control bI system in other way.

class Directive
	regexp = '^.[a-z]+[ \\t]*[^\\n]*\\n'

#	@init {										'adaptive constructor'
#		%tag  = %value * '^\.[a-z]+'
#		value = %value - '^\.[a-z]+\s+'
#	}

Directive object modify themself for dynamic class mutation.

.sec- Control

Directive .end		'stop translation'			regexp = '^\\.end'
Directive .module	'set current module'		regexp = '^\\.module'
Directive .file		'create file inline'		regexp = '^\\.file'

.sec- Metadata

Directive .title	'title for current module'	regexp = '^\\.title'
Directive .author	'(c) author <email>'		regexp = '^\\.author'
Directive .license	'<url> to license page'		regexp = '^\\.license'
Directive .github	'<url> to github page'		regexp = '^\\.github'

.sec- Documenting markup

Directive .sec		'define program section'	regexp = '^\.sec\s+'
Directive .sec+		'define program chapter'	regexp = '^\.sec\+\s+'
Directive .sec-		'define program subsection'	regexp = '^\.sec\-\s+'

.sec-  Itemize/enumerate list (not <list> type)

Directive .list		'documentation list'		regexp = '^\.list\s+'
Directive .li		'doc list item'				regexp = '^\.li\s+'

.sec- Modules

Default module from system startup is 'tmp'. Other modules can be created by

Directive .module	'switch/create module'		regexp = '^\.module\s+'

.sec- Inline file definition

bI implements plain text file definitions with computable contents.
Source between \.file and \.eof will be processed into stdout
and copied into selected file with all bI language processing.

Directive .file		'define file contents'		regexp = '^\.file\s+'
Directive .eof		'end inline file'			regexp = '^\.eof'

.sec+ Generics (primitive data types)

Generic bI language types provides highlevel abstracts for typical primitive
data types in other programming languages. Generics is gateway between machine
level types, and bI metaprogramming hell: it have all debug, profiling and
tracking functions, but can be transparently transformed into primitive types
for statical compilation, native machine code or hardware synthesis.

Current bI supports only machine numeric types, covered by C++ alias types.

.sec Numbers
# numbers

 -1		 +02	 003	 0x12AF		 0b1101		 -01.23		 -04e-056  +0.4E-056
?-1		?+02	?003	?0x12AF		?0b1101		?-01.23		?-04e-056 ?+0.4E-056
$-1		$+02 	$003	$0x12AF		$0b1101		$-01.23		$-04e-056 $+0.4E-056

 1234567890		?1234567890		$1234567890		# max
 12345678901	?12345678901	$12345678901	# overflow

class Number

.sec String

Most unversal data type, can represent and data in serialized form.

class String

.sec+ Machine types

Machine types was inherited from LLVM design, and uses LLVM itself for code
generation.

.list
.li [iN]teger, N=2^n
.li [f]loat, [d]ouble
.li [v]ector

.sec Memory elements

.sec- i1: bool

clazz bool:		i1
clazz byte:		i8
clazz short:	i16
clazz word:		i32
clazz long:		i64

.sec Number

.sec- int: integer

class int :Number	'integer'					regexp = '[0-9]+'

0 -1 +2 -03 +004

.sec- hex: hexadecimal

class hex:Number	'hexadigital'				regexp = '0x[0-9A-F]+'

.sec- bin: binary

Number bin			'binary'					regexp = '0b[01]+'

0x12AF 0b1101

.sec- float: floating point data

Number float		'float'						regexp = '[0-9]+[eE][+-]?[0-9]+'

1.2 -3e+04

.sec String

.sec- char: 8-bit classic C char (byte)

clazz char:byte		'8-bit classic C char'		regexp 'any char' =  '.'	

.sec- uchar: unicode character

clazz uchar:char

.sec- str: string

String str			'string'					regexp = "'[^']*'"
	@size		'size in chars'	-> int
	@+(str,str)	'concatenate'	-> str
	@*(str,int)	'repeat str num times'			-> str
	@*(str,str)	'fetch substrings using regexp'	-> list<str>
	@/(str,str)	'split str using regexp'		-> list<str>

.sec+ Object subsystem

.sec Symbols

This ?is $a symbol.

All elements in bI system based on Symbol class:

class Symbol

.sec+ bI system model

.sec core Object class

clazz Object 'core bI data'
	tag		'class/data type marker'
	value	'string value'
	attr	'attributes'
	nest	'nested objects'

.sec+ Sources (with bI-computed substitutions)

.file lexer.lpp
%{
$AUTOGEN

\#include "bI.hpp"

\#define TC(X)	{ yylval.c = yytext[\0];     			return X; }
\#define T\1(X)	{ yylval.c = yytext[\1];					return X; }
\#define TS(X)	{ yylval.s = new string(yytext);     	return X; }
\#define TO(C,X)	{ yylval.o = new biObject(C,yytext); 	return X; }
\#define TX(C,X)	{ yylval.o = new C(yytext); 			return X; }
%}

%option noyywrap
%option yylineno

S	[\+\-]{\0,\1}
D	[\0-\9]+

%%
$LEXER_RULES
%%
.eof

.file parser.ypp
$AUTOGEN
.eof

.file bI.hpp
$AUTOGEN
.eof

.file core.cpp
$AUTOGEN
.eof

.sec+ C++ runtime

.end
###############################################################################
###############################################################################


.sec+ Data types

.sec+ 

.sec String

g,str
	class		'class name'
	value		'generic value'

'string1' $'string2' ?'string3'

.sec Symbol

Any text string not detected as other literal, treated as symbol.
Symbol represents themself in dump, evaluation, and its value.

class Symbol,sym
	lexer regexp = '[a-zA-Z_][a-zA-Z_0-9]+' # classical ID char set

$biClass $Symbol,id
?biClass ?Symbol,id

.sec Number

Float and integer processing is too different, Number type holds shared
semantics.

#class Number
#	lexer regexp (
#		S : '[\-\+]{0,1}'		# optional +/- sign
#		D : '[0-9]+'			# decimal digits group
#	)
#	@dump -> %					# dump it as is
#	@eval -> %					# eval it as is
#class int: Number

Number Integer,int	lexer regexp NUM = '{S}{D}'			# integers like -1 +2
Number hex			lexer regexp NUM = '0x[0-9A-Z]+'	# hex literals
Number bin			lexer regexp NUM = '0b[01]+'		# bin literals

Number Float,float
	lexer regexp (
		'{S}{D}\.{D}'		# dotted floats like -12.34
		'{S}{D}[eE]{S}{D}'	# exponential form -7e+8
	)	

$00 $-01 $+0002 $0x1234 $0b1101
$-3.4 $5.6 $+7.8
$-1e+3 $+4E-5

?00 ?-01 ?+0002 ?0x1234 ?0b1101
?-3.4 ?5.6 ?+7.8
?-1e+3 ?+4E-5

-oriented design

.sec Base class inheritance

Core class can be created using this syntax (start with first char in line):

class Class,alias,es vars @and @signals inline
	'also docstring for class'
	and some
	extra			'with their'
	variables 		
	@and @signals	'own docstrings'

.sec Object

Generic object implements all bI-specific features for all other data types.

#class Object
	str name	'class name'
	str value	'some textual value'
	@dump		'serializer/dumper'					-> '<'+cls+':'+val+'>'
	@load(str)	'deserialize constructor/loader'	-> %
	@eval		'evaluate (compute)'				-> % # as is

.sec \% current object itself marker (this, self)

\% symbol marks current object (like self and this in other languages).

.sec Signal as object method

bI uses SmallTalk like passing signals between objects, but have
inkernel multiagent parallel computing ideology, and this signals is real
async messages, not function calls.

\@signal marks signal a.k.a. class method:

class Signal,sig
	lexer regexp SIG = '@[a-z0-9_\+\-\*\/]+'
	parser SIG list<type>

Extended signal definiton uses Erlang-like pattern mathching: is uses match
pattern defined via type argument list.

.sec Data in nested variables

Data stored in object using nested variables.
All objects includes two required vars: name and value.

.sec+ Containers (composite types)

#class Container
#	@size	-> int	# content size
#	@+=		-> %	# add element

.sec Pair

Container Pair parser = expr ':' expr

$this:is ?pair:sample
$1:2 ?3.4:5e6
$e:2.71 ?pi:3.1415

.sec List

$(1)
$1,2
$1,2,3

.sec+ Deploy control

.sec Modules

Directive \.module creates/switches current module. In base bI realization
module mapped to directory, and controls \.file directive path for new files.

Module 'tmp' used by default after bI system starts.
This done for preventing current bI files overwrite.

.sec File creation

You can use \.file and \.eof directives for direct file creation (in current
module only for sequrity reasons):

.file README.md
\# ALYEH platform
\#\# ALYEH:dYnamic language bI
\#\#\# developer/experimental branch
.eof

.sec+ GUI extension

# class Rect int Width; int Height

#class Display: Rect int ColorDepth; str ID

#class Color

#class Window : Rect

.sec+ Symbolic computation engine

.module sym

.sec lexer

.file lexer.lpp
%{
\#include "sym.hpp"
\#define T(C,X)	{ yylval.s=new sym(C,yytext); return X; }
%}

%option noyywrap
%option yylineno

S	[\\+\\-]\?
D	[0-9]+

%%
\#[^\\n]*				T("comment",S)	/* comment line */
[\\+\\-\\*\\/\\^]		T("op",S)		/* operator */
[\\<\\>\\.\\,]			T("op",S)
[=;]					T("op",S)
:						T("colon",COLON)
[\\(\\)\\{\\}\\[\\]]	T("par",S)		/* parens */
\\"[^\\n\\"]*\\"		T("str",S)		/* string */
\\'[^\\\n\\']*\\'		T("str",S)		/* string */
{D}						T("num",S)		/* integer number, no prefix sign */
0x[a-zA-Z0-9]+			T("num",S)		/* hex number */
0b[01]+					T("num",S)		/* bin number */
{D}\\.{D}				T("num",S)		/* float number in dotted form */
{D}[eE]{S}{D}			T("num",S)		/* float number in exponential form */
[a-zA-Z_][a-zA-Z_0-9]*	T("sym",S)		/* symbol */
%[TFN]|%				T("sym",S)		/* special */
[ \\t\\r]+				{}				/* drop spaces */
\\n+					T("eol",EOL)
.						T("char",S)		/* any undetected data as char */
%%
.eof

class file
	name
	mode

class lexer
	file : lpp
	file : hpp

#lexer sym
#	'\#[^\\n]*'	,	'comment'	,	COMMENT
#	'[0-9]+'	,	'num'		,	NUM


.sec parser
.file parser.ypp
%{
\#include "sym.hpp"
%}

%defines

%union {
	sym *s;
}

%token	<s>		S EOL COLON
%type	<s>		ex list

%%
sym :
	| sym EOL		{ cout << "<eol>\\n\\n"; }
	| sym list		{ cout << *\$2->dump() << *\$2->eval() << "\\n" ; }
	| sym ex		{ cout << *\$2->dump() << *\$2->eval() << "\\n" ; }
;

ex :
	  S				{ \$\$=\$1; }
	| S COLON S		{ \$\$=new sym("pair",\$1,\$3); }
;

list :
	   ex ex		{ \$\$=new sym("list",\$1,\$2); }
	 | list ex		{ \$\$=\$1; \$\$->next.push_back(\$2); }
;
%%
.eof

.sec Test suite

.file test.bI
\#!/usr/bin/sym
\# this is line comment # required by UNIX first script line
\#

\# symbols
this is generic symbols
But iT _can be in 0Any ClAssical ID form including n00mber_s.
Leading 01Fdigits treated as number with unknown base.

\# numbers: sym engine treat all number as symbols
0 -1 +2 -03 04 +05 0x12AFG 0b11010110

\# special symbols

true %T false %F nil %N this/self %

/# operators and float numbers

+1+-2/03*4.5^-6e+7

\# strings: sym as is

'this " is ' "a ' string"

\# composite data

\# pair

1.2:3e5 1:2 3 :4 5: 6

\# list
1 2
1 2 3

.eof

.sec Generic Symbol

.sec Object

All elemenents in sym is objects.

clazz Symbol,sym		'generic sym data type'
	string Class,cls	'class name'
	string Value,val	'value for leaf symbols'
	list<sym> Attrib,attr 'list of optional symbol attributes'
	list<sym> Nest,nest	'list for non-leaf (nested) symbols'
	@dump -> str		'string representation of internal structure (sym dump)'
	@eval -> str		'string representation of sym value (sym compute)'
	@load str -> %		'constructor creates symbol object from dump string'
	lexer {				'lexer constructor uses regexp matching for sym creation'
		comment = '#[^\\n]*'			'comment line'
		space = '[ \t\r\n]+':%N			'drop any spaces'
		sym = '[a-zA-Z_][a-zA-Z_0-9]*'	'symbol'
		special = '%[TFN]'				'special symbols true/false/nil'
		operator = '[\+\-\*\n]'			'operator'
		num = '[a-zA-Z0-9]+'			'number in any base, no prefix sign'
		char = '.':%					'treat any char as symbol by default'
	} -> %

.sec- Attributes

Every symbol can have optional assigned attributes.
Attributes widely used as misc data element markers in syntax analisis,
XML processing and data storage, thus they are supported by special list field.

.sec- Leaf objects

Every symbol has two string fields: Class name and Value.

.sec- Non-leaf objects

Every symbol has optional List field which can contain links to other symbols.

.sec- Serialization and computing

.list Every symbol can be represented in two forms using signals
.li @eval compute symbol (recursively) into string Value.
.li @dump dump symbol into string representation

Dump can be user for objects serializaton, storage, network messaging,..
using @load constructor method.


$1,2,3


branch: old master

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


