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

class Directive
	lexer regexp = '^\.[a-z]+[\+\-]?[ \t]*[^\n]*'
	@init {
		%[class] = %[value] * '\.[a-z]+' [first] # rename class for new object
		%[value] = %[value] - '^\.[a-z]+[ \t]*' # remove leading .some<space>
	}
class .file: Directive
	lexer regexp = '^\.file[ \t]+[^\n]+'

Directive object modify themself using first '.some' string from 
Directive[val] field for dynamic class rename.

.sec \\ escape char

\\ escape char is prefix before any special char marks use this char as is.

.sec Comments

Comments must be removed from output.
# line comments until end of line 

class Comment

class LineComment:Comment lexer regexp = '#[^\n]*'

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

.sec+ Directive

Elements starting with . is directives, controls mainly document generation,
but can control other language system functions.

class Directive lexer regexp DOT = '\.[a-z]+[\+\-]?[ \t]+[^\n]*'

.sec \.title: current (sub)module title.
.sec \.author: author marker
.sec \.github: GutHub marker
.sec \.module: define (sub)module
.sec \.file \.eof: create file contents intext
.sec \.sec \.sec+ \.sec-: sectioning, mark contents items

Directive .sec lexer regexp = '\.sec[^\n]+'

.sec \.list \.li: itemize/enumerate list (not <list> type)

.sec+ Data types

.sec+ Generics (primitive data types)

Generic bI language types provides highlevel abstracts for typical primitive
data types in other programming languages. Generics is gateway between machine
level types, and bI metaprogramming hell: it have all debug, profiling and 
tracking functions, but can be transparently transformed into primitive types
for statical compilation, native machine code or hardware synthesis.

.sec String

Most unversal data type, can represent and data in serialized form.

class String,str
	class		'class name'
	value		'generic value'
	@size		'size in chars'					-> int
	@+(str,str)	'concatenate'					-> str
	@*(str,int)	'repeat str num times'			-> str
	@*(str,str)	'fetch substrings using regexp'	-> list<str>
	@/(str,str)	'split str using regexp'		-> list<str>

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

class Number
	lexer regexp (
		S : '[\-\+]{0,1}'		# optional +/- sign
		D : '[0-9]+'			# decimal digits group
	)
	@dump -> %					# dump it as is
	@eval -> %					# eval it as is
class int: Number

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

.sec Machine types

Machine types was inherited from LLVM design, and uses LLVM itself for code 
generation. 

.list
.li [iN]teger, N=2^n
.li [f]loat, [d]ouble
.li [v]ector

.sec+ Object-oriented design

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

class Container
	@size	-> int	# content size
	@+=		-> %	# add element

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

class Rect int Width; int Height

class Display: Rect int ColorDepth; str ID

class Color

class Window : Rect

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

S	[\\+\\-]{0,1}
D	[0-9]+

%%
\#[^\\n]*				T("comment",S)	/* comment line */
[ \\t\\r\\n]+			{}				/* drop spaces */
[\\+\\-\\*\\/\\^]		T("op",S)		/* operator */
[\\<\\>\\.\\,]			T("op",S)
[=:;]					T("op",S)
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
.						T("char",S)		/* any undetected data as char */
%%
.eof

.sec parser
.file parser.ypp
%{
\#include "sym.hpp"
%}

%defines 

%union {
	sym *s;
}

%token <s> S

%%
sym :
	| sym S { cout << *\$2->dump() << "\\t" << *\$2->eval() << "\\n" ; } 
;
%%
.eof

.sec C++ runtime

.file sym.hpp
\#ifndef _H_SYM
\#define _H_SYM

\#include <iostream>
\#include <cstdio>
\#include <cstdlib>
\#include <cassert>
\#include <map>
\#include <list>

using namespace std;

struct sym {
	string *cls;				// class name
	string *val;				// symbol value
	list<sym*> attr;			// attributes
	list<sym*> next;			// nested symbols (for non-leaf symbol)
	sym(const char*,char*);		// constructor (class,value)
	virtual string* dump();		// dump symbol
	virtual string* eval();		// evaluate (compute) symbol into string value
};

extern int yylex();
extern int yyparse();
extern int yylineno;
extern char *yytext;
extern void yyerror(string);
\#include "parser.tab.hpp"

\#endif // _H_SYM
.eof

.file sym.cpp
\#include "sym.hpp"

sym::sym(const char *C, char *V) { 
	cls = new string( C ); val = new string( V );
	if (*cls=="comment") val->erase(0,1); // del \#
}

string* sym::dump()	{ return new string( "<" + *cls + ":" + *val + ">" ); }
string* sym::eval()	{ return val; }

void yyerror(string err) { 
	cerr<<"\\n"<<err<<" \# "<<yylineno<<" : "<<yytext<<"\\n\\n";
	exit(-1);
}

int main(int argc, char *argv[]) { 
	cout<<"\\n\# "<<argv[0]<<"\\n\\n"; 
	return yyparse(); 
}
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

.eof

.file Makefile
.eof

.sec Generic Symbol

.sec Object

All elemenents in sym is objects.

class Symbol,sym		'generic sym data type'
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


